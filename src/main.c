#include "../inc/cub3d.h"

int main(void)
{
    t_cub   cub;

    init_cub(&cub);
    if(init_mlx(&cub))
    {
        free_cub(&cub);
        return (1);
    }
    render_smoke_frame(&cub);
    setup_hooks(&cub);
    mlx_loop(cub.mlx.ptr);
    free_cub(&cub);
    return (0);
}
