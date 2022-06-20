// SPDX-License-Identifier: MIT

pragma solidity ^0.8.0;

import "TrustworthyRockPaperScissorsTournamentSpecs.sol";

contract TrustworthyRockPaperScissorsTournament is TrustworthyRockPaperScissorsTournamentSpecs {
    enum Move { ROCK, PAPER, SCISSOR }
    enum Status { IN_PROGRESS, END }
    struct PlayerInfo {
        address payable id;
        uint8 wins;
        Move[] games;
        uint fees;
    }

    mapping(Player => PlayerInfo) players;
    uint8 target;
    uint256 matchFee;
    Status status;
    Player winner;
    address payable owner;

    uint8 override public disputedMatches;
 
    constructor(
        address payable firstPlayer,
        address payable secondPlayer,
        uint8 targetWins,
        uint256 singleMatchFee
    ) {
        require(firstPlayer != secondPlayer, "Players must be two different addresses.");
        require(firstPlayer != address(0) && secondPlayer != address(0), "Players address are not valid.");

        players[Player.First].id = firstPlayer;
        players[Player.Second].id = secondPlayer;
        target = targetWins;
        matchFee = singleMatchFee;
        status = Status.IN_PROGRESS;
        disputedMatches = 0;
        owner = payable(msg.sender);
    }

    function moveRock() external override payable {
        move(Move.ROCK);
    }

    function movePaper() external override payable {
        move(Move.PAPER);
    }

    function moveScissor() external override payable {
        move(Move.SCISSOR);
    }

    modifier mustBeAPlayer() {
        require(msg.sender == players[Player.First].id || msg.sender == players[Player.Second].id, "You're not one of the players.");
        _;
    }

    function move(Move move_type) internal mustBeAPlayer {
        require(status != Status.END, "Game has already finish");
        require(msg.value >= matchFee, "You need to pass the minimum fee to play");

        Player p = (msg.sender == players[Player.First].id ? Player.First : Player.Second);
        players[p].games.push(move_type);
        players[p].fees += msg.value;

        checkGame();
    }

    function checkGame() internal {
        uint8 n = uint8(
                players[Player.First].games.length < players[Player.Second].games.length 
                ? players[Player.First].games.length
                : players[Player.Second].games.length
            );

        for (uint8 i = disputedMatches; i < n; ++i) {
            Move p1 = players[Player.First].games[i];
            Move p2 = players[Player.Second].games[i];

            // Fair play
            if (p1 == p2) continue;

            if (
                (p1 == Move.ROCK && p2 == Move.SCISSOR) ||
                (p1 == Move.SCISSOR && p2 == Move.PAPER) ||
                (p1 == Move.PAPER && p2 == Move.ROCK)
            ) {
                players[Player.First].wins++;
                emit MatchWonBy(Player.First, i);
            } else {
                players[Player.Second].wins++;
                emit MatchWonBy(Player.Second, i);
            }

            disputedMatches++;

            if (players[Player.First].wins == target) {
                emit TournamentWonBy(Player.First);
                winner = Player.First;
                endGame();
            } else if (players[Player.Second].wins == target) {
                emit TournamentWonBy(Player.Second);
                winner = Player.Second;
                endGame();
            }
        }
    }

    function endGame() internal {
        require(status != Status.END, "Game has already finish");

        assert(players[winner].wins == target);

        uint total = players[Player.First].fees + players[Player.Second].fees;
        assert(total == address(this).balance);
        players[winner].id.transfer(total);

        status = Status.END;
        selfdestruct(owner);
    }
}
