#pragma once

#include <random>
#include <iostream>
#include <deque>
#include <Windows.h>

#include "board.h"

const int global_depth = 4;

struct node {
	board b;
	node* parent;
	std::vector<node*> childs;
	int value;

	node(board _b)
	{
		b = _b;
		parent = nullptr;
		value = get_value();
	}

	node(board _b, node* _p)
	{
		b = _b;
		parent = _p;
		value = get_value();
	}

	int get_value()
	{
		int c_1 = 0;
		int c_2 = 0;
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (b.els[i][j] == 1)
					c_1++;
				else if (b.els[i][j] == 2)
					c_2++;
			}
		}
		return c_1 - c_2;
	}

	void generate_possible_moves()
	{
		std::vector<node*> result;
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				if (b.els[i][j] == b.turn)
				{
					for (int ii = 0; ii < 6; ++ii)
					{
						for (int jj = 0; jj < 6; ++jj)
						{
							int l = b.move_len(i, j, ii, jj);
							if (b.els[ii][jj] == 0 && (l == 1 || l == 2))
							{
								board* new_board = new board{ b.els, b.turn, b.opp };
								new_board->move(i, j, ii, jj, l);
								node* new_node = new node{ *new_board, this };
								result.push_back(new_node);
							}
						}
					}
				}
			}
		}
		this->childs = result;
	}
};

node* make_move(node* from_node)
{
	auto b = from_node->b;

	std::string from, to;
	std::cin >> from >> to;

	b.move(from, to);

	return new node{ b };
}

void abprun()
{
	int h = 5;
	int now_h = 0;

	board b = board();
	node* root = new node{ b };


	node* first = root;

	first->generate_possible_moves();

	while (!first->b.is_over())
	{
		for (int i = 0; i < first->childs.size(); ++i)
		{
			first->childs[i]->generate_possible_moves();
		}
		first = first->childs[0];
	}

	std::deque<node*> solution;
	while (first->parent != nullptr)
	{
		solution.push_back(first);
		first = first->parent;
	}


	reverse(solution.begin(), solution.end());
	solution.push_front(root);

	for (auto x : solution)
	{
		x->b.print();
		Sleep(100);
		printf("\033c");
	}
}



void create_tree(node* root, int depth)
{
	if (depth == global_depth)
		return;
	root->generate_possible_moves();
	for (int i = 0; i < root->childs.size(); ++i)
	{
		create_tree(root->childs[i], depth + 1);
	}

}

static bool compare(node* a, node* b)
{
	return a->value < b->value;
}

node* compute_next_step(node* from)
{
	/*int alpha = INT32_MIN;
	int beta = INT32_MAX;*/

	if (from->childs.size() == 0)
		return from;

	if (from->b.turn == 1)
	{
		return *std::max_element(from->childs.begin(), from->childs.end(), compare);
	}
	else
	{
		*std::min_element(from->childs.begin(), from->childs.end(), compare);
	}
}

void ab()
{
	board b = board();
	node* root = new node{ b };

	node* x = root;
	x->b.print();
	while (!root->b.is_over())
	{
		if (root->b.turn == 1)
		{
			create_tree(root, 0);
			x = compute_next_step(root);
			x->b.print();
		}
		else
		{
			x = make_move(root);
			x->b.print();
		}
		root = x;
	}
}