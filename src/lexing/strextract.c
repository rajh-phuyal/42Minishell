/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strextract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c <jalves-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:25:00 by jalves-c          #+#    #+#             */
/*   Updated: 2024/02/20 21:25:01 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_quotes(char input, bool *inside_double_quotes, \
								bool *inside_single_quotes)
{
	if (is_double_quote(input) && !(*inside_single_quotes))
		*inside_double_quotes = !(*inside_double_quotes);
	else if (is_single_quote(input) && !(*inside_double_quotes))
		*inside_single_quotes = !(*inside_single_quotes);
}

/**
 * * remove_spaces
 * @brief 	if one or multiple spaces are found outside
 * 			of a quotes, they are replaced by the separator
 * 			E.g.: hello        world "   again"
 * 				hello\world\"   again" <- where \ is the separator
 * @param input is the input string
 * @param separator the char used to replace the spaces
*/
static char	*remove_spaces(char *input, char separator)
{
	t_inside	inside;
	char		*modified;
	char		*dst;
	char		*temp;

	inside = (t_inside){false, false};
	modified = ft_calloc(1, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	dst = modified;
	temp = input;
	while (*input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (is_space(*input) && !inside.dquotes && !inside.squotes)
		{
			if (dst == modified || !is_space(*(dst - 1)))
				*(dst++) = separator;
		}
		else
			*(dst++) = *input;
		input++;
	}
	free(temp);
	return (modified);
}

/**
 * * isolate_char
 * @brief	if the target char is found inside the
 * 			input string (outside of single or double quotes)
 * 			it is isolated by the separator. E.g.: hello>1 becomes hello > 1
 * @param input is the input string
 * @param target is the target char
 * @param separator the char used to isolate the target in the input
*/

static char	*isolate_char(char *input, char target, char separator, int i)
{
	t_inside	inside;
	char		*modified;
	char		*temp;

	inside = (t_inside){false, false};
	modified = (char *)ft_calloc(3, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	temp = input;
	while (input && *input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (*input == target && !inside.dquotes && !inside.squotes)
		{
			modified[i++] = separator;
			modified[i++] = *input;
			modified[i++] = separator;
		}
		else
			modified[i++] = *input;
		input++;
	}
	free(temp);
	return (modified);
}

/**
 * * isolate_compund
 * @brief	if the target string is found inside the
 * 			input string (outside of single or double quotes)
 * 			it is isolated by the separator. E.g.: hello>>1 becomes hello >> 1
 * @param input is the input string
 * @param target is the target string
 * @param separator the char used to isolate the target in the input
*/
static char	*isolate_compound(char *input, char *target, char separator, int i)
{
	t_inside	inside;
	char		*temp;
	char		*modified;

	inside = (t_inside){false, false};
	modified = (char *)ft_calloc(3, ft_strlen(input) + 1);
	if (!modified)
		return (NULL);
	temp = input;
	while (input && *input)
	{
		toggle_quotes(*input, &inside.dquotes, &inside.squotes);
		if (*input == target[FIRST_ELEM] && *(input + 1) == target[SECOND_ELEM] \
			&& inside.dquotes == false && inside.squotes == false)
		{
			modified[i++] = separator;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = (*(input++)) * -1;
			modified[i++] = separator;
		}
		else
			modified[i++] = *(input++);
	}
	free(temp);
	return (modified);
}

/**
 * * strextract
 * @brief		spaces, isolates special chars and
 * 				splits the input string into a vector 2D ARRAY
 * @param 		minivault is a pointer to the "general" structure
 * @param		input is the input string
*/

char	*strextract(char *line)
{
	char	*temp;

	line = remove_spaces(line, '\31');
	if (!line)
		return (NULL);
	line = isolate_compound(line, ">>", '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_compound(line, "<<", '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '|', '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '<', '\31', 0);
	if (!line)
		return (NULL);
	line = isolate_char(line, '>', '\31', 0);
	temp = line;
	while (temp && *temp)
	{
		*temp = ft_abs(*temp);
		temp++;
	}
	return (line);
}
