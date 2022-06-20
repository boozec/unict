// SPDX-License-Identifier: MIT

pragma solidity >0.7 <0.9;

contract RandomMoney {
    uint public total;
    uint public constant minFee = 10;
    mapping(address => uint) public amounts;
    address[] private members;


    function play() public payable returns (uint) {
        require(msg.value >= minFee, "Value is less than the required minimum");


        amounts[msg.sender] += msg.value;

        if (amounts[msg.sender] == msg.value) {
            members.push(msg.sender);
        }

        total += msg.value;

        return total;
    }

    function pay() public payable {
        address payable account = payable(randomAddress());
        account.transfer(total);
        total = 0;
    }

    function randomAddress() internal view returns (address) {
        uint8 num = uint8(
            uint256(
                keccak256(abi.encode(block.timestamp, block.difficulty))
            ) % members.length
        );

        return members[num];
    }
}

