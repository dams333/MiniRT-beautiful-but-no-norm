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
					point.c \
					sec_degree_utils.c \
					to_cylindrical.c \
					to_spherical.c \
					vector.c \
					vector_scalar_operation.c \
					matrix.c \
					angle.c \
				) \
				$(addprefix render/, \
					events.c \
					mlx_utils.c \
					render_manager.c \
					compute_pixel.c \
					compute_lights.c \
					bump_map.c \
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
CFLAGS		=   -O3 -g3 #-Wall -Werror -Wextra
INCLUDE		=	-I includes/ -I libs/minilibx-linux/
LIBS		=	libs/libft/libft.a libs/minilibx-linux/libmlx.a
EXT_LIBS	=	-lm -lX11 -lXext

all		:	$(NAME)

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(EXT_LIBS) -o $(NAME)

$(LIBS)	:	FORCE
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib);\
		make -C $$(dirname $$lib);\
	done

FORCE	:

clean	:	
	rm -Rf build/

cleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) clean;\
		make -C $$(dirname $$lib) clean;\
	done

cleanall	:	clean cleanlibs


fclean	:	clean
	rm -f ${NAME}

fcleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) fclean;\
		make -C $$(dirname $$lib) fclean;\
	done

fcleanall	:	fclean fcleanlibs


re		:	fclean ${NAME}

relibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) re;\
		make -C $$(dirname $$lib) re;\
	done

reall	: relibs re

-include $(OBJS_DEPEND)

.PHONY	:	all clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall libs
