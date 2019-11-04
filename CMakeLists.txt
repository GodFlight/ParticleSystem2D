cmake_minimum_required(VERSION 3.14)
project(Particle_System C)

set(CMAKE_C_STANDARD 11)

set(GCC_COMPILE_FLAGS "-O2")

link_directories(/Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.10/lib)
link_directories(/Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5/lib)

include_directories(include)
include_directories(Libft/include)



add_executable(Particle_System
        include/stb_image.h
        Libft/include/get_next_line.h
        Libft/include/libft.h
        Libft/src/ft_abs.c
        Libft/src/ft_atoi.c
        Libft/src/ft_bzero.c
        Libft/src/ft_clear_double_pointer.c
        Libft/src/ft_fswap.c
        Libft/src/ft_isalnum.c
        Libft/src/ft_isalpha.c
        Libft/src/ft_isascii.c
        Libft/src/ft_isdigit.c
        Libft/src/ft_isprint.c
        Libft/src/ft_isstn.c
        Libft/src/ft_itoa.c
        Libft/src/ft_itoa_base.c
        Libft/src/ft_lstadd.c
        Libft/src/ft_lstdel.c
        Libft/src/ft_lstdelone.c
        Libft/src/ft_lstiter.c
        Libft/src/ft_lstmap.c
        Libft/src/ft_lstnew.c
        Libft/src/ft_lstnormdel.c
        Libft/src/ft_lstnormdelone.c
        Libft/src/ft_memalloc.c
        Libft/src/ft_memccpy.c
        Libft/src/ft_memchr.c
        Libft/src/ft_memcmp.c
        Libft/src/ft_memcpy.c
        Libft/src/ft_memdel.c
        Libft/src/ft_memmove.c
        Libft/src/ft_memset.c
        Libft/src/ft_putchar.c
        Libft/src/ft_putchar_fd.c
        Libft/src/ft_putendl.c
        Libft/src/ft_putendl_fd.c
        Libft/src/ft_putnbr.c
        Libft/src/ft_putnbr_fd.c
        Libft/src/ft_putstr.c
        Libft/src/ft_putstr_fd.c
        Libft/src/ft_quick_sort.c
        Libft/src/ft_sort_bubl.c
        Libft/src/ft_strcat.c
        Libft/src/ft_strchr.c
        Libft/src/ft_strclr.c
        Libft/src/ft_strcmp.c
        Libft/src/ft_strcpy.c
        Libft/src/ft_strdel.c
        Libft/src/ft_strdup.c
        Libft/src/ft_strequ.c
        Libft/src/ft_strhash.c
        Libft/src/ft_striter.c
        Libft/src/ft_striteri.c
        Libft/src/ft_strjoin.c
        Libft/src/ft_strlcat.c
        Libft/src/ft_strlen.c
        Libft/src/ft_strmap.c
        Libft/src/ft_strmapi.c
        Libft/src/ft_strncat.c
        Libft/src/ft_strncmp.c
        Libft/src/ft_strncpy.c
        Libft/src/ft_strnequ.c
        Libft/src/ft_strnew.c
        Libft/src/ft_strnstr.c
        Libft/src/ft_strrchr.c
        Libft/src/ft_strsplit.c
        Libft/src/ft_strstr.c
        Libft/src/ft_strsub.c
        Libft/src/ft_strtrim.c
        Libft/src/ft_strwcnumber.c
        Libft/src/ft_swap.c
        Libft/src/ft_tolower.c
        Libft/src/ft_toupper.c
        Libft/src/ft_updt.c
        Libft/src/get_next_line.c include/particale_system.h main.c)

target_include_directories(Particle_System PRIVATE /Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.10/include/SDL2)
target_include_directories(Particle_System PRIVATE /Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5/include/SDL2)
target_link_libraries(Particle_System
        "SDL2"
        "SDL2_image"
        "-framework AppKit"
        "-framework OpenGL"
        "-framework OpenCL"
        )
