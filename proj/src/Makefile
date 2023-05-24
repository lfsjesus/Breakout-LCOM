# Nome do binário. Tem de ser "proj".
PROG=proj

# Indicar as pastas de todos os ficheiros a compilar.
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/controller/keyboard_mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/view/
.PATH: ${.CURDIR}/controller/game


# Ficheiros ".c" a compilar. Têm de estar contidos nas pastas indicadas no passo anterior.
SRCS = 	main.c timer.c utils.c graphics.c kbc.c keyboard.c mouse.c view.c sprite.c model.c ball.c brick.c paddle.c game.c

# Flags de compilação
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# Dependências
DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>