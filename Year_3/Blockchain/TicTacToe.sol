// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

contract TicTacToe {
    enum Player { X, O }
    struct PlayerInfo {
        address payable id;
        Player p_type;
    }
    enum Cell { X, O, NONE }
    enum GameStatus { TURN_X, TURN_O, WAIT, END }

    mapping(address => PlayerInfo) players;
    address[2] playerIds;
    Cell[3][3] cells;
    Player turn;
    GameStatus status = GameStatus.WAIT;
    uint immutable minFee;
    uint fee;
    uint8 moves = 9;

    event Movement(address sender, Player player, Cell[3][3] cells);
    event EndGame(address winner, uint amount);

    constructor(address payable firstPlayer, address payable secondPlayer, uint _minFee) {
        require(firstPlayer != address(0) && secondPlayer != address(0), "You must define both address");
        require(firstPlayer != secondPlayer, "Players must be different");

        players[firstPlayer] = PlayerInfo({
            id: firstPlayer,
            p_type: Player.X
        });
        playerIds[0] = firstPlayer;
        players[secondPlayer] = PlayerInfo({
            id: secondPlayer,
            p_type: Player.O
        });
        playerIds[1] = secondPlayer;
        minFee = _minFee;
        turn = Player(getRandomTurn());

        for (uint8 i = 0; i < 3; ++i)
            for (uint8 j = 0; j < 3; ++j)
                cells[i][j] = Cell.NONE;
    }

    function play(uint x, uint y) public payable {
        require(status != GameStatus.END, "Game is over");
        require(players[msg.sender].id != address(0), "You're not one of the players");
        require(players[msg.sender].p_type == turn, "It's not your turn");
        require(msg.value >= minFee, "Value is less than the min fee");

        fee += msg.value;

        if (cells[y][x] != Cell.NONE) {
            revert("Can't use this cell");
        }

        cells[y][x] = (turn == Player.X ? Cell.X : Cell.O);
        turn = Player(1 - uint(turn));
        moves--;
        checkGame();
    }

    function getBoard() public view returns (Cell[3][3] memory) {
        return cells;
    }

    /*
    -------------
    |   |   |   |
    |---|---|---|
    |   |   |   |
    |---|---|---|
    |   |   |   |
    -------------
    */

    function checkGame() internal {
        // It's useless to check when moves > 4
        if (moves > 4) return;

        bool result = false;
        PlayerInfo memory winner;

        if (moves == 0) {
            emit EndGame(address(this), fee);
            status = GameStatus.END;
        }

        // Diagonal wins
        if (
            (cells[0][0] == cells[1][1] && cells[0][0] == cells[2][2]) ||
            (cells[0][2] == cells[1][1] && cells[0][2] == cells[2][0])
        ) {
            address addr = address(0);
            if (cells[0][0] != Cell.NONE) {
                addr = playerIds[uint256(cells[0][0])];
                winner = players[addr];
                assert(uint(winner.p_type) == uint(cells[0][0]));
                result = true;
            } else if (cells[0][2] != Cell.NONE) {
                addr = playerIds[uint256(cells[0][2])];
                winner = players[addr];
                assert(uint(winner.p_type) == uint(cells[0][2]));
                result = true;
            }
        }

        if (!result) {
            for (uint8 i = 0; i < 3; i+=3) {
                for (uint8 j = 0; j < 3; j+=3) {
                    if (cells[i][j] == Cell.NONE) continue;

                    address addr = playerIds[uint256(cells[i][j])];

                    if (
                        (cells[i][j] == cells[i+1][j] && cells[i][j] == cells[i+2][j]) ||
                        (cells[i][j] == cells[i][j+1] && cells[i][j+1] == cells[i][j+2])
                    ) {
                        result = true; 
                    }

                    if (result) {
                        winner = players[addr];
                        assert(uint(winner.p_type) == uint(cells[i][j]));
                        break;
                    }

               }

                if (result) break;
            }
        }

        if (result && winner.id != address(0)) {
            assert(fee == address(this).balance);
            winner.id.transfer(fee);
            status = GameStatus.END;
            emit EndGame(winner.id, fee);
            fee = 0;
        }
    }

    function getRandomTurn() internal view returns (uint8) {
        return uint8(
            uint256(
                keccak256(abi.encode(block.timestamp, block.difficulty))
            ) % 2
        );
    }
}
