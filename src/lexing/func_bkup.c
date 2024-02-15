// static	char	*alchemy(t_minivault *minivault, t_strexp *data, char *iter)
// {
// 	char	temp;
// 	char	*value;
// 	char	*_built;
// 	char	*suffix;

// 	data->pos = iter;
// 	iter++;
// 	temp = '\0';
// 	_built = NULL;
// 	suffix = NULL;
// 	while (iter && *iter)
// 	{
// 		if (!*(iter + 1) || *iter == DOLLAR || \
// 			*iter == '\'' || *iter == '"')
// 		{
// 			temp = *iter * (*(iter + 1) > 0);
// 			*iter = (*iter) * !(*(iter + 1) > 0);
// 			if (data->pos && *(data->pos + 1) == PREVEXITSTAT[FIRST_ELEM])
// 			{
// 				suffix = get_suffix(data->pos + 2);
// 				value = get_env(minivault, PREVEXITSTAT);
// 			}
// 			else if (data->pos)
// 				value = get_env(minivault, data->pos + 1);
// 			if (value)
// 			{
// 				if (*(iter) == '\'' && *(data->pos - 1) == '\'')
// 				{
// 					if (!_built)
// 						_built = exe_concat(_built, value, suffix, NULL);
// 					else
// 						_built = exe_concat(_built, "'",
// 							_built, "'", value, suffix, NULL);
// 				}
// 				if (!_built)
// 					_built = exe_concat(_built, "", value, suffix, NULL);
// 				else
// 					_built = exe_concat(_built, _built, value, suffix, NULL);
// 				if (suffix)
// 				{
// 					free(suffix);
// 					suffix = NULL;
// 				}
// 			}
// 			if (temp)
// 			{
// 				*iter = temp;
// 				temp = '\0';
// 			}
// 			if (*iter == DOLLAR)
// 				data->pos = iter;
// 			else
// 				data->pos = NULL;
// 		}
// 		iter++;
// 	}
// 	if (!_built)
// 		_built = exe_concat(NULL, PLACEHOLDER, NULL);
// 	else if (_built && data->singleq)
// 		_built = exe_concat(_built, "'", _built, "'", NULL);
// 	return (_built);
// }

// void	strexpand(t_minivault *minivault, char **vector)
// {
// 	t_strexp	data;
// 	char		*s_iter;
// 	char		*_magic;
// 	char		**v_iter;

// 	v_iter = vector;
// 	while (v_iter && *v_iter)
// 	{
// 		s_iter = *v_iter;
// 		_cleaner(&data);
// 		_exp_validator(s_iter, &data);
// 		if (_check_heredoc_deli(s_iter, vector))
// 		{
// 			printf("is this expandable: %s | %d\n", s_iter, data.expandable);
// 			while (s_iter && *s_iter)
// 			{
// 				if (*s_iter == DOLLAR && data.expandable)
// 				{
// 					if (!*(s_iter + 1))
// 						break ;
// 					_put_end_break(s_iter + 1, &data);
// 					_magic = alchemy(minivault, &data, s_iter);
// 					if (!_magic)
// 						break ;
// 					*(s_iter - (data.quoted + data.singleq)) = '\0';
// 					_magic = exe_concat(_magic, *v_iter, _magic, NULL);
// 					free(*v_iter);
// 					*v_iter = _magic;
// 					break ;
// 				}
// 				s_iter++;
// 			}
// 		}
// 		v_iter++;
// 	}
// }