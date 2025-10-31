# ---------- Configurações ----------
NAME        = so_long

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
NC          = \033[0m

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3
INCLUDE     = -I libft/srcs/includes -I include
MLX 		= -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd

RM          = rm -rf
RUNLIB      = -C libft
RUNMLX      = -C minilibx-linux

# Diretórios
SRCSDIR     = srcs
OBJDIR      = objs

# Fontes
SRCS 		= main.c				\
			utils.c					\
			utils2.c				\
			check_map.c				\
			read_map.c				\
			load_sprites.c			\
			mlx_utils.c				\
			moves.c					\
			update.c				\
			update_utils.c			\
			render_map.c			\
			draw_tile.c				\
			draw_sky.c				\
			move_horizontal.c		\
			move_vertical.c			\
			ft_rand.c				\
			ft_dtoa.c				\
			inits.c					\
			closer.c				\
			print_msg.c				\
			player.c				\
			mob.c					\
			mob_ia.c				\
			check_reachability.c		

# Adiciona prefixo do diretório
SRCS := $(addprefix $(SRCSDIR)/, $(SRCS))

# Objetos
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Libs
LIBFT = libft/libft.a
MLX_LIB = minilibx-linux/libmlx.a

# ---------- Regras ----------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@printf "$(GREEN)🎉 Executável $(NAME) criado com sucesso!$(NC)\n"

# Compilar objetos
$(OBJDIR)/%.o: $(SRCSDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(YELLOW)⚙️ Compilando %s -> %s$(NC)\n" "$<" "$@"

# Criar pasta objs se não existir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compilar libft silenciosamente
$(LIBFT):
	@$(MAKE) $(RUNLIB) -s
	@printf "$(GREEN)✅ Libft compilada com sucesso$(NC)\n"

# Compilar minilibx silenciosamente
$(MLX_LIB):
	@$(MAKE) $(RUNMLX) -s > /dev/null 2>&1
	@printf "$(GREEN)✅ MiniLibX compilada com sucesso$(NC)\n"

# Limpeza
clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) clean $(RUNLIB) -s
	@$(MAKE) clean $(RUNMLX) -s > /dev/null 2>&1
	@printf "$(YELLOW)🧹 Objetos limpos$(NC)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean $(RUNLIB) -s
	@printf "$(YELLOW)🗑️ Executável removido$(NC)\n"

re: fclean all

.PHONY: all clean fclean re
