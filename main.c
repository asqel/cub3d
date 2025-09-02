/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmansa <lucmansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:29:31 by lucmansa          #+#    #+#             */
/*   Updated: 2025/08/12 18:05:53 by lucmansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void prnt_info(t_game ctx)
{
	int i;

	i = -1;
	while (ctx.map[++i])
		printf("|%s|\n", ctx.map[i]);
	printf("p_x : %f, p_y : %f\n", ctx.p_x, ctx.p_y);
	printf("map height : %i, map width : %i\n", ctx.map_height, ctx.map_width);
	printf("ddddddddddd %d\n", ctx.map[3][9]);
}

int	main(int argc, char **argv)
{
	static t_game	ctx;

	ctx.ceil_col = 0xFF000000;
	ctx.floor_col = 0xFF000000;
	if (argc != 2)
		return (c3d_set_err(ERR_ARG), c3d_print_err(), 1);
	if (launch_parsing(&ctx, argv[1]))
		return (c3d_print_err(), c3d_exit(&ctx, 1), 1);
	prnt_info(ctx);
	c3d_init(&ctx, argc, argv);
	ctx.buffer = (uint32_t *)mlx_get_data_addr(ctx.mlx.backbuffer,
			&argc, &argc, &argc);
	mlx_hook(ctx.mlx.win, KeyPress, KeyPressMask, (void *)key_pressed, &ctx);
	mlx_hook(ctx.mlx.win, KeyRelease, KeyReleaseMask,
		(void *)key_released, &ctx);
	mlx_loop_hook(ctx.mlx.mlx, (void *)tick_hook, &ctx);
	mlx_loop(ctx.mlx.mlx);
}
