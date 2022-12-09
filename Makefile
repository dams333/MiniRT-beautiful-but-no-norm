NAME		=	miniRT

SRCS		=	main.c \
				$(addprefix parser_bonus/, \
					parser.c \
					parse_c_a.c \
					parse_l_cy.c \
					parse_sp_pl.c \
					parse_el.c \
					parse_util.c \
					parse_util2.c \
					parse_util3.c \
					generate_list.c \
					parse_bonus.c \
				) \
				$(addprefix geometric/, \
					cross_product.c \
					distance_between_points.c \
					dot_product.c \
					get_intersecting_time_through_ray_with_cylinder.c \
					get_intersecting_time_through_ray_with_ellipsoid.c \
					get_intersecting_time_through_ray_with_plane.c \
					get_intersecting_time_through_ray_with_sphere.c \
					get_intersecting_time_through_ray_with_tube.c \
					get_intersecting_obj.c \
					get_nearest_positive_intersection.c \
					get_point_through_ray_at_time.c \
					get_rotation_angles.c \
					point.c \
					rotate.c \
					sec_degree_utils.c \
					to_cylindrical.c \
					to_ellipsoidal.c \
					to_spherical.c \
					vector.c \
					vector_scalar_operation.c \
					matrix.c \
					angle.c \
				) \
				$(addprefix render/, \
					bump_map.c \
					compute_lights.c \
					compute_pixel.c \
					events.c \
					load_checkerboard_color.c \
					mlx_utils.c \
					render_manager.c \
					textures.c \
				) \
				$(addprefix interactions/, \
					interactions_manager.c \
					move.c \
					resize.c \
					view.c \
					rotate.c \
				) \
				$(addprefix checkerboard/, \
					is_3d_filled.c \
					is_filled.c \
					to_checkerboard_pos.c \
				)


_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

CC			=	cc
CFLAGS		=   -O3 -g3
INCLUDE		=	-I includes/ -I libs/minilibx-linux/
LIBFT		=	libs/libft/libft.a
LIBMLX		=	libs/minilibx-linux/libmlx.a
EXT_LIBS	=	-lm -lX11 -lXext

DEFINE	=	-D BONUS=1

all		:	$(NAME)

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} ${DEFINE} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBFT) $(LIBMLX) $(LIBMLX)
	$(CC) $(CFLAGS) ${DEFINE} $(OBJS) $(LIBFT) $(LIBMLX) $(EXT_LIBS) -o $(NAME)

-include $(OBJS_DEPEND)

$(LIBFT): FORCE
	make -C libs/libft
$(LIBMLX): FORCE
	make -C libs/minilibx-linux
FORCE:

clean	:	
	rm -Rf build/

cleanlibs	:
	make -C libs/libft clean
	make -C libs/minilibx-linux clean

cleanall	:	clean cleanlibs


fclean	:	clean
	rm -f ${NAME}
	rm -f ${NAME_BONUS}

fcleanlibs	:
	make -C libs/libft fclean
	make -C libs/minilibx-linux clean

fcleanall	:	fclean fcleanlibs


re		:	fclean ${NAME}


reall	: relibs re

.PHONY	:	all clean cleanlibs libs cleanall fclean fcleanlibs fcleanall re relibs reall libs
