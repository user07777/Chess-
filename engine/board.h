#pragma once
namespace chess {
	enum boardEnum {
		white = 0xfff,
		black = 0xC0FFE
	};
	struct Board {
		bool init() {
			//peças
			for (auto& i : starting_positions) {
				auto name = i.first;
				if (isupper( name )) {
					//brancas
					 // { "R", { 'a', 1 } }  -> Rook , {x,y}
					switch (name) {
					case 'R':  Board.push_back( std::make_shared<Rook>( i.second, name ) ); break;
					case 'B':  Board.push_back( std::make_shared<Bishop>( i.second, name ) ); break;
					case 'N':  Board.push_back( std::make_shared<Knight>( i.second, name ) ); break;
					case 'K':  Board.push_back( std::make_shared<King>( i.second, name ) ); break;
					case 'Q':  Board.push_back( std::make_shared<Queen>( i.second, name ) ); break;
					default: {
#ifndef __linux__
						OutputDebugStringA( "peça invalida!" );
#endif
						return false;
					}
					}
				}
				else {
					//pretas
					switch (name) {
					case 'r':  Board.push_back( std::make_shared<Rook>( i.second, name ) ); break;
					case 'b':  Board.push_back( std::make_shared<Bishop>( i.second, name ) ); break;
					case 'n':  Board.push_back( std::make_shared<Knight>( i.second, name ) ); break;
					case 'k':  Board.push_back( std::make_shared<King>( i.second, name ) ); break;
					case 'q':  Board.push_back( std::make_shared<Queen>( i.second, name ) ); break;
					default: {
#ifndef __linux__
						OutputDebugStringA( "peça invalida!" );
#endif
						return false;
					}
					}
				}
			}

			// Peões
			for (char x = 'a'; x <= 'h'; ++x) {
				Board.push_back( std::make_shared<Pawn>( std::make_pair( x, 2 ), 'P' ) );
				Board.push_back( std::make_shared<Pawn>( std::make_pair( x, 7 ), 'p' ) );
			}
		}
		std::vector< std::shared_ptr < chess::Piece > > Board, nextBoard, prevBoard;
		std::vector<std::pair<int, std::pair<char, int>>> casas;
	};
}