/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:37:50 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/24 11:00:08 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*insert(t_list *data, int id, t_list *aux)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->id = id;
	if (data)
	{
		aux = data;
		while (aux->next != data)
			aux = aux->next;
		aux->next = new;
		new->prev = aux;
		new->next = data;
		data->prev = new;
	}
	else
	{
		new->next = new;
		new->prev = new;
		data = new;
	}
	return (data);
}

t_list	*delete(t_list *data)
{
	t_list	*aux;
	t_list	*next;
	t_list	*first;

	if (!data)
		return (NULL);
	first = data;
	aux = data->next;
	while (aux != first)
	{
		next = aux->next;
		free(aux);
		aux = next;
	}
	free(first);
	return (NULL);
}
