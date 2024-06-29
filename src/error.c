/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:02:07 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/29 21:10:34 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void print_error_msg(int error_code)
{

}

void free_all(void)
{

}

void error_handling(int error_code)
{
    free_all();
    print_error_msg(error_code);
}
