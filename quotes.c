/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:28:08 by mde-figu          #+#    #+#             */
/*   Updated: 2021/10/16 02:18:05 by csantos-         ###   ########.fr       */
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

static char	*expand_var(char *command)
{	
	int		i;
	int		j;
	char	*key;
	char	*val;
	char	*str_start;
	char	*str_end;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '$')
		{
			j = 0;
			while (command[j] != ' ' || command[j] != '\"' || command[j] != '\'' || command[j] != '\0')
				j++;		
			key = ft_substr(command, i, j - i);
			val = search_hash_by_key(key);
			free(key);
			str_start = ft_substr(command, 0, i);
			str_end = ft_substr(command, j, ft_strlen(command) - j);
			free(command);
			command = ft_strjoin(str_start, val);
			command = ft_strjoin(command, str_end);
			free(str_start);
			free(str_end);
		}
		i++;
	}
	return (command);
}

static t_quotes_m *add_quote_list(t_quotes_m *space, t_quotes_m	*new_quote)
{
	t_quotes_m	*tmp;

	new_quote = ft_calloc(1, sizeof(t_quotes_m));
	if (space == NULL)
		space = new_quote;
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
	printf("idx = %d\n", idx);
	while (command[i] != '\0' && i < idx)
	{
	printf("contando string, i = %d, command[i] = %c\n", i, command[i]);
		if (command[i] == ' ')
			string_count++;
		i++;
	}
	printf("i = %d, command[i] = %c\n", i, command[i]);
	//i++;
	j = i;
	printf("q_id = %c\n", q_id);
	while (command[i] != 'q_id') //ESSA COMPARAÇÃO BUGA QUANDO FICA VERDADEIRA
	{
		printf("contando espaço, i = %d, command[i] = %c\n", i, command[i]);
		if (command[i] == ' ')
			space_count++;
		i++;
		printf("contando espaço pós iterada, i = %d, command[i] = %c, space count = %d\n", i, command[i], space_count);
	}
	if (space_count > 0)
	{
		new_quote = NULL;
		new_quote = add_quote_list(space, new_quote);
		new_quote->id_size = space_count - 1;
		new_quote->id = ft_calloc(space_count, sizeof(int));
		while (command[j] != q_id)
		{
			i = 0;
			if (command[j] == ' ')
			{
				command[j] = '@';
				new_quote->id[i] = j - idx;
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
	while (command[i] && i <= (int)ft_strlen(command))
	{
		if (command[i] == '\'')
		{
			if (simple_quote == 0)
				simple_i = i;
			simple_quote++;
			if (simple_quote == 2)
			{
				command = check_space(command, simple_i, '\'', quote_space);
				simple_quote = 0;
			}
		}
		else if (command[i] == '\"')
		{
			if (double_quote == 0)
				double_i = i;
			double_quote++;
			if (double_quote == 2)
			{
				command = check_space(command, double_i, '\"', quote_space);
				double_quote = 0;
			}
		}
		printf("iterando, i = %d, command[i] = %c\n", i, command[i]);
		i = i + 1;
	}
	printf("procurou aspas\n");
	return (command);
}

void	return_spaces(char **splitted, t_quotes_m *quote_space)
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
}

char	**treat_quotes(char *command)
{
	t_quotes_m	*quote_space;
	char		**splitted;

	command = expand_var(command);
	printf("expandiu\n");
	quote_space = NULL;
	command = substitute_quotes(command, quote_space);
	printf("substituiu\n");
	splitted = ft_split(command, ' ');
	printf("splittou\n");
	if (quote_space != NULL)
	{
		return_spaces(splitted, quote_space);
		return (splitted);
	}
	return (splitted);
}
