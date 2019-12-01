/* TODO:
 *
 *
 *
 *
 *
 *
 *
 *	by: Thiago da Silva Baldez
 *				2019
 */

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define LARGURA_TELA 600
#define ALTURA_TELA 600
#define SIZE 5

typedef struct
{
	char name[10];
	int score;
} Player;

void error_msg(char* text)
{
	al_show_native_message_box(NULL, "ERRO",
		"Ocorreu o seguinte erro e o programa sera finalizado:",
		text, NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

int* createMatrix()
{
	int i, randaux;
	time_t t;

	int* gameboard = (int*)calloc(SIZE * SIZE, sizeof(int));

	if (!gameboard)
	{
		error_msg("Falha ao inicializar a Matriz.");
		return NULL;
	}
	

	srand((unsigned)time(&t));

	randaux = rand() % ((SIZE * SIZE) - 1);
	(gameboard)[randaux] = -1;

	for (i = 0; i < 2;)
	{
		randaux = rand() % ((SIZE * SIZE) - 1);
		if ((gameboard)[randaux] == 0)
		{
			(gameboard)[randaux] = 1;
			i++;
		}

	}

	for (i = 0; i < 2;)
	{
		randaux = rand() % ((SIZE * SIZE) - 1);
		if ((gameboard)[randaux] == 0)
		{
			(gameboard)[randaux] = 2;
			i++;
		}

	}

	return gameboard;
}

void updateScreen(int* matrix, int* nextNumber, Player* playerPtr)
{
	int i, j;
	ALLEGRO_FONT* fonte = al_load_font("Arial/arial.ttf", 42, 0);
	ALLEGRO_FONT* fontePlayer = al_load_font("Arial/arial.ttf", 20, 0);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			al_draw_textf(fonte, al_map_rgb(0, 0, 0), (LARGURA_TELA / (SIZE * 2)) * j, (ALTURA_TELA / (SIZE * 2)) * i, ALLEGRO_ALIGN_LEFT, "%d", matrix[i * SIZE + j]);
	}

	// Print Next Number on the Right Bottom Corner
	al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA - 50, ALTURA_TELA - 75, ALLEGRO_ALIGN_LEFT, "%d", *nextNumber);

	// Print Player's Name.
	al_draw_textf(fontePlayer, al_map_rgb(0, 0, 0), LARGURA_TELA - (15 * (strnlen(playerPtr->name, 10))), 10, ALLEGRO_ALIGN_CENTRE, "Name");
	al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA - (15 * (strnlen(playerPtr->name, strnlen(playerPtr->name, 10)))), 40, ALLEGRO_ALIGN_CENTRE, "%s", playerPtr->name);
	al_draw_textf(fontePlayer, al_map_rgb(0, 0, 0), LARGURA_TELA - (15 * (strnlen(playerPtr->name, 10))), 100, ALLEGRO_ALIGN_CENTRE, "SCORE");
	al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA - (15 * (strnlen(playerPtr->name, strnlen(playerPtr->name, 10)))), 130, ALLEGRO_ALIGN_CENTRE, "%d", playerPtr->score);

	al_flip_display();

	al_destroy_font(fonte);
	al_destroy_font(fontePlayer);
}

// Se der tempo, colocar todos os MOVE na mesma função e enviar a tecla apertada como parâmetro.
bool moveUp(int* matrix, bool isAtest, Player* playerPtr)
{
	int i, j, offset, aboveLine, thirdline;
	for (i = 1; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{

			offset = i * SIZE + j;
			aboveLine = offset - SIZE;
			//thirdline = offset - SIZE * 2;

			if (i == 1)
			{
				if ((matrix)[offset] != -1)
				{
					if ((((matrix)[aboveLine]) == 0) && (((matrix)[offset]) != 0))
					{
						if (!isAtest)
						{
							((matrix)[aboveLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if ((matrix)[aboveLine] + (matrix)[offset] == 3)
					{
						if (!isAtest)
						{
							if (((matrix)[aboveLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[aboveLine]);

						}
						else
							return true;
					}

					else if (((matrix)[offset] > 2) && ((matrix)[aboveLine] == ((matrix)[offset])))
					{
						if (!isAtest)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[aboveLine]);
						}
						else
							return true;
					}
				}
			}
			else
			{
				thirdline = offset - SIZE * 2;

				if ((matrix)[offset] != -1)
				{
					if (((matrix)[aboveLine] == 0) && ((matrix)[offset] != 0))
					{
						if (!isAtest)
						{
							((matrix)[aboveLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[aboveLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							if (((matrix)[aboveLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[aboveLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[aboveLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							((matrix)[aboveLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[aboveLine]);
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveDown(int* matrix, bool isAtest, Player* playerPtr)
{
	int i, j, offset, belowLine, thirdline;
	for (i = (SIZE - 2); i > -1; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = i * SIZE + j;
			belowLine = offset + SIZE;

			if (i == (SIZE - 2))
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[belowLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[belowLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[belowLine] + (matrix)[offset] == 3)
					{
						if (!isAtest)
						{
							if (((matrix)[belowLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[belowLine]);
						}
						else
							return true;

					}
					else if (((matrix)[offset] > 2) && ((matrix)[belowLine] == ((matrix)[offset])))
					{
						if (!isAtest)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[belowLine]);
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset + SIZE * 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[belowLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[belowLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[belowLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							if (((matrix)[belowLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[belowLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[belowLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							((matrix)[belowLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[belowLine]);
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveLeft(int* matrix, bool isAtest, Player* playerPtr)
{
	int i, j, offset, leftLine, thirdline;
	for (i = 1; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE) + i;
			leftLine = offset - 1;
			//thirdline = offset - 2;

			if (i == 1)
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[leftLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[leftLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[leftLine] + (matrix)[offset] == 3)
					{
						if (!isAtest)
						{
							if (((matrix)[leftLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[leftLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[leftLine] == ((matrix)[offset])))
					{
						if (!isAtest)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[leftLine]);
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset - 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[leftLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[leftLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[leftLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							if (((matrix)[leftLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[leftLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[leftLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							((matrix)[leftLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[leftLine]);
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool moveRight(int* matrix, bool isAtest, Player* playerPtr)
{
	int i, j, offset, rightLine, thirdline;
	for (i = (SIZE - 2); i > -1; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE) + i;
			rightLine = offset + 1;
			thirdline = offset + 2;

			if (i == (SIZE - 2))
			{
				if ((matrix)[offset] != -1)
				{
					if ((matrix)[rightLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[rightLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}
					else if ((matrix)[rightLine] + (matrix)[offset] == 3)
					{
						if (!isAtest)
						{
							if (((matrix)[rightLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[rightLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[rightLine] == ((matrix)[offset])))
					{
						if (!isAtest)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[rightLine]);
						}
						else
							return true;
					}

				}
			}
			else
			{
				thirdline = offset + 2;

				if ((matrix)[offset] != -1)
				{
					if ((matrix)[rightLine] == 0)
					{
						if (!isAtest)
						{
							((matrix)[rightLine]) = ((matrix)[offset]);
							((matrix)[offset]) = 0;
						}
						else
							return true;
					}

					else if (((matrix)[rightLine] + (matrix)[offset] == 3) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							if (((matrix)[rightLine] != 0) && ((matrix)[offset] != 0))
								playerPtr->score += 3;

							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							//(*score) += ((matrix)[rightLine]);
						}
						else
							return true;
					}
					else if (((matrix)[offset] > 2) && ((matrix)[rightLine] == ((matrix)[offset])) && ((matrix)[thirdline] != 0))
					{
						if (!isAtest)
						{
							((matrix)[rightLine]) += ((matrix)[offset]);
							((matrix)[offset]) = 0;
							playerPtr->score += ((matrix)[rightLine]);
						}
						else
							return true;
					}
				}
			}
		}
	}

	return false;
}

bool hasPossibleMove(int* matrix, Player* playerPtr)
{
	if (moveUp(matrix, true, playerPtr))
		return true;
	else if (moveDown(matrix, true, playerPtr))
		return true;
	else if (moveLeft(matrix, true, playerPtr))
		return true;
	else if (moveRight(matrix, true, playerPtr))
		return true;
	else
		return false;
}

void addNumber(int* matrix, int button, int* nextNumber)
{
	int i, j, emptyIndex = 0, offset, randAux, possibleIndex[SIZE];
	time_t t;

	srand((unsigned)time(&t));

	if (button == ALLEGRO_KEY_UP)
	{
		for (i = 1; i <= SIZE; i++)
		{
			offset = (SIZE * SIZE) - i;
			if (((matrix)[offset]) == 0)
			{
				possibleIndex[emptyIndex] = offset;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
	else if (button == ALLEGRO_KEY_DOWN)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (((matrix)[i]) == 0)
			{
				possibleIndex[emptyIndex] = i;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
	else if (button == ALLEGRO_KEY_LEFT)
	{
		for (i = 1; i <= SIZE; i++)
		{
			offset = (i * SIZE) - 1;
			if (((matrix)[offset]) == 0)
			{
				possibleIndex[emptyIndex] = offset;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}

	}
	else if (button == ALLEGRO_KEY_RIGHT)
	{
		for (j = 0; j < SIZE; j++)
		{
			offset = (j * SIZE);
			if (((matrix)[offset]) == 0)
			{
				possibleIndex[emptyIndex] = offset;
				emptyIndex++;
			}
		}

		if (emptyIndex != 0)
		{
			do
			{
				randAux = rand() % emptyIndex;
				randAux = possibleIndex[randAux];
			} while ((matrix)[randAux] != 0);

			(matrix)[randAux] = *nextNumber;
		}
	}
}

int generateNextNumber(int* matrix)
{
	int nextNumber, randIndex;
	time_t t;

	srand((unsigned)time(&t));
	do
	{
		randIndex = rand() % ((SIZE * SIZE) - 1);
		nextNumber = (matrix)[randIndex];
	} while (nextNumber == -1);

	if (nextNumber == 0)
	{
		do
		{
			nextNumber = rand() % 3;
		} while (nextNumber == 0);
	}
	else if (nextNumber == 1)
	{
		nextNumber = 2;
	}
	else if (nextNumber == 2)
	{
		nextNumber = 1;
	}

	return nextNumber;
}

void loginScreen(Player* playerPtr, ALLEGRO_DISPLAY* display)
{
	ALLEGRO_EVENT event;
	int namecont = 0, i;
	char j = 0;
	const char* aux = NULL;
	bool leave;

	playerPtr->name[0] = '\0';
	playerPtr->score = 0;

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	ALLEGRO_FONT* fonte = al_load_font("Arial/arial.ttf", 48, 0);

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(255, 255, 0));
	al_flip_display();


	do {

		al_flip_display();
		al_wait_for_event(event_queue, &event);
		leave = false;

		fflush(stdin);

		if (event.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (j < 10)
			{
				for (i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_Z; i++)
				{
					if (event.keyboard.keycode == i)
					{
						al_clear_to_color(al_map_rgb(255, 255, 0));
						aux = al_keycode_to_name(i);
						playerPtr->name[j] = *aux;
						j++;
						al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2, ALLEGRO_ALIGN_CENTRE, "%s", playerPtr->name);
						al_flip_display();
						break;
					}
				}
			}
		}
		else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (event.keyboard.keycode == ALLEGRO_KEY_ENTER))
		{
			leave = true;
		}
		else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) && (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE))
		{
			if (j > 0)
			{
				j--;
				playerPtr->name[j] = '\0';
				al_clear_to_color(al_map_rgb(255, 255, 0));
				al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, ALTURA_TELA / 2, ALLEGRO_ALIGN_CENTRE, "%s", playerPtr->name);
				al_flip_display();
			}
		}

	} while (!leave || (playerPtr->name[0] == '\0'));

	al_destroy_font(fonte);
	al_destroy_event_queue(event_queue);
}

void endGame(Player* playerPtr, ALLEGRO_DISPLAY* display, FILE* fileptr, Player *scoreboardadress)
{
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_FONT* fonte = al_load_font("Arial/arial.ttf", 48, 0);

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	fwrite(scoreboardadress, sizeof(Player) * 10, 1, fileptr);
	//fwrite(playerPtr, sizeof(Player), 1, fileptr);
	fclose(fileptr);

	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_flip_display();

	al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA / 2) - 75, ALLEGRO_ALIGN_CENTRE, "%s", playerPtr->name);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA / 2), ALLEGRO_ALIGN_CENTRE, "Score");
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, (ALTURA_TELA / 2) + 75, ALLEGRO_ALIGN_CENTRE, "%d", playerPtr->score);

	while (true)
	{
		al_flip_display();
	}

}

int main()
{
	int* gameboard = NULL, nextNumber;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_EVENT event;
	Player player, scoreboard[10];

	memset(scoreboard, 0, sizeof(scoreboard));


	if (!al_init())
	{
		error_msg("Falha ao inicializar a Allegro");
		return -1;
	}

	al_init_font_addon();

	if (!al_init_ttf_addon())
	{
		error_msg("Falha ao inicializar add-on allegro_ttf");
		return -1;
	}

	font = al_load_font("Arial/arial.ttf", 32, 0);
	if (!font)
	{
		error_msg("Falha ao carregar fonte.");
		return -1;
	}

	if (!al_install_mouse())
		return 1;

	if (!al_install_keyboard())
		return 1;

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	if (event_queue == NULL)
		return 1;

	display = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!display)
	{
		error_msg("Falha ao criar janela");
		return -1;
	}

	gameboard = createMatrix();
	if (!gameboard)
	{
		al_destroy_display(display);
		error_msg("Falha ao carregar a Matriz do Jogo.");
		return -1;
	}

	FILE* fileptr = fopen("Scoreboard.bin", "r+");
	if (fileptr)
	{
		fread(scoreboard, sizeof(Player) * 10, 1, fileptr);
	}

	fileptr = fopen("Scoreboard.bin", "w+");

	loginScreen(&player, display);

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(255, 255, 255));
	nextNumber = generateNextNumber(gameboard);
	updateScreen(gameboard, &nextNumber, &player);
	al_flip_display();

	while (1) // GameLoop
	{
		al_wait_for_event(event_queue, &event);

		if (al_event_queue_is_empty(event_queue))
		{
			al_flip_display();
			updateScreen(gameboard, &nextNumber, &player);
		}

		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			al_destroy_font(font);
			al_destroy_event_queue(event_queue);
			al_destroy_display(display);
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				//pauseGame();
				al_destroy_font(font);
				al_destroy_event_queue(event_queue);
				al_destroy_display(display);
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				if (moveUp(gameboard, true, &player))
				{
					moveUp(gameboard, false, &player);
					addNumber(gameboard, event.keyboard.keycode, &nextNumber);
					nextNumber = generateNextNumber(gameboard);
					updateScreen(gameboard, &nextNumber, &player);
				}

				if (!hasPossibleMove(gameboard, &player))
				{
					endGame(&player, display, fileptr, scoreboard);
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				if (moveDown(gameboard, true, &player))
				{
					moveDown(gameboard, false, &player);
					addNumber(gameboard, event.keyboard.keycode, &nextNumber);
					nextNumber = generateNextNumber(gameboard);
					updateScreen(gameboard, &nextNumber, &player);
				}

				if (!hasPossibleMove(gameboard, &player))
				{
					endGame(&player, display, fileptr, scoreboard);
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				if (moveRight(gameboard, true, &player))
				{
					moveRight(gameboard, false, &player);
					addNumber(gameboard, event.keyboard.keycode, &nextNumber);
					nextNumber = generateNextNumber(gameboard);
					updateScreen(gameboard, &nextNumber, &player);
				}

				if (!hasPossibleMove(gameboard, &player))
				{
					endGame(&player, display, fileptr, scoreboard);
				}
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				if (moveLeft(gameboard, true, &player))
				{
					moveLeft(gameboard, false, &player);
					addNumber(gameboard, event.keyboard.keycode, &nextNumber);
					nextNumber = generateNextNumber(gameboard);
					updateScreen(gameboard, &nextNumber, &player);
				}

				if (!hasPossibleMove(gameboard, &player))
				{
					endGame(&player, display, fileptr, scoreboard);
				}
			}

			break;
		}
	}

	return 0;
}