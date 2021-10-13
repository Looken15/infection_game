#pragma once

#include <iostream>
#include <string>

struct board {
	int els[6][6];
	int turn = 1;

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
		memcpy(els, e, sizeof(int) * 16);
	}

	void print()
	{
		std::cout << "   a b c d e f\n";
		for (int i = 0; i < 6; ++i)
		{
			std::cout << i + 1 << "  ";
			for (int j = 0; j < 6; ++j)
			{
				std::cout << els[i][j] << " ";
			}
			std::cout << "\n";
		}
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
				turn = turn == 1 ? 2 : 1;
			}
			else if (len == 2)
			{
				els[xt][yt] = turn;
				els[xf][yf] = 0;
				turn = turn == 1 ? 2 : 1;
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

private:
	int move_len(std::string from, std::string to)
	{
		int dx = std::abs(from[0] - to[0]);
		int dy = std::abs(from[1] - to[1]);
		return std::max(dx, dy);
	}
};