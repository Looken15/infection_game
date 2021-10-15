#pragma once

#include <iostream>
#include <string>
#include <vector>

struct board {
	int els[6][6];
	int turn = 1;
	int opp = turn == 1 ? 2 : 1;

	board()
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				els[i][j] = 0;
			}
		}
		els[0][0] = 1;
		els[0][5] = 2;
		els[5][0] = 2;
		els[5][5] = 1;
	}

	board(int e[6][6])
	{
		memcpy(els, e, sizeof(int) * 36);
	}

	board(int e[6][6], int _t, int _o)
	{
		memcpy(els, e, sizeof(int) * 36);
		turn = _t;
		opp = _o;
	}

	void print()
	{
		std::cout << "   a b c d e f\n";
		for (int i = 0; i < 6; ++i)
		{
			std::cout << i + 1 << "  ";
			for (int j = 0; j < 6; ++j)
			{
				if (els[i][j] == 1) std::cout << "+ ";
				else if (els[i][j] == 2) std::cout << "- ";
				else std::cout << "O" << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void move(std::string from, std::string to)
	{
		int xf = from[1] - 49;
		int yf = from[0] - 97;
		int xt = to[1] - 49;
		int yt = to[0] - 97;

		if (els[xf][yf] == turn && els[xt][yt] == 0)
		{
			int len = move_len(from, to);
			if (len == 1)
			{
				els[xt][yt] = turn;
				infect(xt, yt);
				turn = turn == 1 ? 2 : 1;
				opp = opp == 1 ? 2 : 1;
			}
			else if (len == 2)
			{
				els[xt][yt] = turn;
				els[xf][yf] = 0;
				infect(xt, yt);
				turn = turn == 1 ? 2 : 1;
				opp = opp == 1 ? 2 : 1;
			}
			else
			{
				std::cout << "Неверный ход! Попробуйте ещё раз\n";
			}
		}
		else
		{
			std::cout << "Неверный ход! Попробуйте ещё раз!\n";
		}
	}

	void move(int xf, int yf, int xt, int yt, int len)
	{
		if (len == 1)
		{
			els[xt][yt] = turn;
			infect(xt, yt);
			turn = turn == 1 ? 2 : 1;
			opp = turn == 2 ? 1 : 2;
		}
		else if (len == 2)
		{
			els[xt][yt] = turn;
			els[xf][yf] = 0;
			infect(xt, yt);
			turn = turn == 1 ? 2 : 1;
			opp = opp == 1 ? 2 : 1;
		}
	}

	void play()
	{
		print();

		std::string from, to;
		std::cin >> from >> to;

		while (from != "q")
		{
			printf("\033c");
			move(from, to);
			print();

			std::cin >> from >> to;
		}
	}

	bool is_over()
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (els[i][j] == 0) return false;
			}
		}
		return true;
	}

	std::vector<board*> generate_possible_moves()
	{
		//opp = turn == 1 ? 2 : 1;
		std::vector<board*> result;
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (els[i][j] == turn)
				{
					for (int ii = 0; ii < 6; ++ii)
					{
						for (int jj = 0; jj < 6; ++jj)
						{
							int l = move_len(i, j, ii, jj);
							if (els[ii][jj] == 0 && (l == 1 || l == 2))
							{
								board* new_board = new board{ els, turn,opp };
								new_board->move(i, j, ii, jj, l);
								result.push_back(new_board);
							}
						}
					}
				}
			}
		}
		return result;
	}

	int move_len(std::string from, std::string to)
	{
		int dx = std::abs(from[0] - to[0]);
		int dy = std::abs(from[1] - to[1]);
		return std::max(dx, dy);
	}

	int move_len(int xf, int yf, int xt, int yt)
	{
		int dx = std::abs(xf - xt);
		int dy = std::abs(yf - yt);
		return std::max(dx, dy);
	}

	void infect(int x, int y)
	{
		for (int i = x - 1; i < x + 2; ++i)
		{
			for (int j = y - 1; j < y + 2; ++j)
			{
				try_infect(i, j);
			}
		}

	}

	void try_infect(int x, int y)
	{
		if (x >= 0 && x <= 5 && y >= 0 && y <= 5 && els[x][y] == opp)
			els[x][y] = turn;
	}
};