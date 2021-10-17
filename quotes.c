/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:28:08 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/16 23:43:50 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* void	quote_commander(char **cmd)
{
	int j;
	int k;

	j = 0;
	while (cmd[0][j])
	{
		if (cmd[0][j] == '\"' || cmd[0][j] == '\'')
		{
			k = j + 1;
			while (cmd[0][k])
			{
				if (cmd[0][k] == cmd[0][j]) 
				{
					cmd[0][j] = ' ';
					cmd[0][k] = ' ';
					break;
				}
				k++;
			}
			j = k - 1;
		}
		j++;
	}
} */

static char	*expand_var(char *command) //sequencia de $ não tá funcionando
{	
	int		i[2];
	char	*key;
	char	*val;
	char	*str_start;
	char	*str_end;

	i[0] = 0;
	while (command[i[0]] != '\0')
	{
		if (command[i[0]] == '$')
		{
			i[1] = i[0] + 1;
			while (command[i[1]] != ' ' && command[i[1]] != D_QUOTE && command[i[1]] != S_QUOTE && (command[i[1]]))
			{
				//ft_printf("command[i[1]] = %c, TRUE=%d\n", command[i[1]], command[i[1]] != ' ');
				i[1]++;		
			}
			//ft_printf("i[0] = %d, command[i[0]] = %c, i[1] = %d, command[i[1]] = %d\n", i[0], command[i[0]], i[1], command[i[1]]);
			key = ft_substr(command, i[0] + 1, i[1] - i[0] - 1);
			//ft_printf("key = |%s|\n", key);
			val = search_hash_by_key(key);
			//ft_printf("val = |%s|\n", val);
			free(key);
			str_start = ft_substr(command, 0, i[0]);
			//ft_printf("str_sta = |%s|\n", str_start);
			str_end = ft_substr(command, i[1], ft_strlen(command) - i[1]);
			//ft_printf("str_end = |%s|\n", str_end);
			free(command);
			key = ft_strjoin(str_start, val);
			//ft_printf("str_sta + val = |%s|\n", key);
			command = ft_strjoin(key, str_end);
			//ft_printf("str_expandida = |%s|\n", str_start);
			free(str_start);
			free(str_end);
			free(key);
		}
		i[0]++;
	}
	return (command);
}

static t_quotes_m *add_quote_list(t_quotes_m *space, t_quotes_m	*new_quote)
{
	t_quotes_m	*tmp;

	new_quote = ft_calloc(1, sizeof(t_quotes_m));
	tmp = space;
	while (tmp->next_quote != NULL)
		tmp = tmp->next_quote;
	tmp->next_quote = new_quote;
	return (new_quote);
}

static char *subs_quote(char *command, int idx, char q_id)
{
	char	*str_start;
	char	*str_end;

	str_start = ft_substr(command, 0, idx);
	str_end = ft_substr(command, idx + 1, ft_strlen(command) - idx + 1);
	free(command);
	command = ft_strjoin(str_start, str_end);
	free(str_start);
	free(str_end);
	while (command[idx] != q_id)
		idx++;
	str_start = ft_substr(command, 0, idx);
	str_end = ft_substr(command, idx + 1, ft_strlen(command) - idx + 1);
	free(command);
	command = ft_strjoin(str_start, str_end);
	free(str_start);
	free(str_end);
	return (command);
}

static char	*check_space(char *command, int idx, char q_id, t_quotes_m *space)
{
	t_quotes_m	*new_quote;
	int			space_count;
	int			string_count;
	int			i;
	int			j;

	i = 0;
	space_count = 0;
	string_count = 0;
	while (command[i] != '\0' && i < idx)
	{
		if (command[i] == ' ')
			string_count++;
		i++;
	}
	//printf("string_count = %d\n", string_count);
	i++;
	j = i;
	while (command[i] != q_id)
	{
		if (command[i] == ' ')
			space_count++;
		i++;
	}
	//printf("space_count = %d\n", space_count);
	if (space_count > 0)
	{
		new_quote = NULL;
		new_quote = add_quote_list(space, new_quote);
		new_quote->id_size = space_count - 1;
		new_quote->id = ft_calloc(space_count, sizeof(int));
		new_quote->split_c = string_count;
		//printf("id_size = %d\n", new_quote->id_size);
		i = 0;
		while (command[j] != q_id)
		{
			if (command[j] == ' ')
			{
				command[j] = '@';
				new_quote->id[i] = j - idx - 1;
				//printf("index = [%d]%d\n", i, new_quote->id[i]);
				i++;
			}
			j++;
		}
	}
	command = subs_quote(command, idx, q_id);
	return (command);
}

static char	*substitute_quotes(char *command, t_quotes_m *quote_space)
{
	int			simple_quote;
	int			double_quote;
	int			i;
	int			simple_i;
	int			double_i;
	
	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == S_QUOTE)
		{
			if (simple_quote == 0)
				simple_i = i;
			simple_quote++;
			if (simple_quote == 2)
			{
				command = check_space(command, simple_i, S_QUOTE, quote_space);
				i = 0;
				double_quote = 0;
				simple_quote = 0;
			}
		}
		else if (command[i] == D_QUOTE)
		{
			if (double_quote == 0)
				double_i = i;
			double_quote++;
			if (double_quote == 2)
			{
				command = check_space(command, double_i, D_QUOTE, quote_space);
				i = 0;
				simple_quote = 0;
				double_quote = 0;
			}
		}
		i++;
	}
	return (command);
}

/* void	return_spaces(char **splitted, t_quotes_m *quote_space)
{
	t_quotes_m	*tmp;

	tmp = NULL;
	while (quote_space->next_quote != NULL)
	{
		while (quote_space->id_size >= 0)
		{
			splitted[quote_space->split_c][quote_space->id[quote_space->id_size]] = ' ';
			quote_space->id_size--;
		}
		free(quote_space->id);
		tmp = quote_space->next_quote;
		free(quote_space);
		quote_space = tmp;
	}
	while (quote_space->id_size >= 0)
	{
		splitted[quote_space->split_c][quote_space->id[quote_space->id_size]] = ' ';
		quote_space->id_size--;
	}
	free(quote_space->id);
	free(quote_space);
} */

static char	**bring_spaces_back(char **splitted, t_quotes_m *space_lst)
{
	t_quotes_m		*tmp;

	tmp = NULL;
	if (space_lst->next_quote != NULL)
		tmp = space_lst->next_quote;
	free(space_lst);
	space_lst = tmp;
	if (space_lst == NULL)
		return (splitted);
	while (space_lst->next_quote != NULL)
	{
		//ft_printf("não entrou aqui, né?\n");
		while (space_lst->id_size >= 0)
		{
			splitted[space_lst->split_c][space_lst->id[space_lst->id_size]] = ' ';
			space_lst->id_size--;
		}
		free(space_lst->id);
		tmp = space_lst->next_quote;
		free(space_lst);
		space_lst = tmp;
	}
	while (space_lst->id_size >= 0)
	{
			//ft_printf("splitted = |%s|, char = |%c|, i = %d, counter = %d\n", splitted[space_lst->split_c], splitted[space_lst->split_c][space_lst->id[space_lst->id_size]], space_lst->id[space_lst->id_size], space_lst->id_size);
		splitted[space_lst->split_c][space_lst->id[space_lst->id_size]] = ' ';
		space_lst->id_size--;
	}
	free(space_lst->id);
	free(space_lst);
	return (splitted);
		
	/* while (space_lst->next_quote != NULL)
	{
		tmp = space_lst->next_quote;
		free(space_lst);
		space_lst = tmp;
		while (space_lst->id_size >= 0)
		{
			splitted[space_lst->split_c][space_lst->id[space_lst->id_size]] = ' ';
			space_lst->id_size--;
		}
	}
	if (space_lst->id)
	{
		while (space_lst->id_size >= 0)
		{
			splitted[space_lst->split_c][space_lst->id[space_lst->id_size]] = ' ';
			space_lst->id_size--;
		}
	}
	free(space_lst);
	return (splitted); */
}

char	**treat_quotes(char *command)
{
	t_quotes_m	*quote_space;
	char		**splitted;

	command = ft_strdup(command);
	//printf("duplicou\n");
	command = expand_var(command);
	//printf("expandiu command = |%s\n", command);
	quote_space = ft_calloc(1, sizeof(t_quotes_m));
	command = substitute_quotes(command, quote_space);
	//printf("substituiu command = |%s\n", command);
	splitted = ft_split(command, ' ');
	//printf("splittou\n");
	splitted = bring_spaces_back(splitted, quote_space);
	free(command);
//	return_spaces(splitted, quote_space);
	return (splitted);
}
