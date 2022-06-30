// Cariotti 1000001948
// SPDX-License-Identifier: MIT

pragma solidity ^0.8.0;

import "./exam-2022-06-24-specs.sol";

contract MafiaToken is ERC20, MafiosoTokenSpecs {
    enum Role { USER, PICCIOTTO, GODFATHER }
    struct Mafioso {
        address id;
        uint tokens;
        Role role;
        bool active;
        uint8 children;
    }
    
    struct Approve {
        address owner;
        uint amount;
    }

    mapping(address => Mafioso) mafiosi;
    address[] address_users;
    address public override immutable godfather;
    mapping(address => Approve[]) approves;


    uint public override totalSupply;

    uint8 private pizzo; // Use `pizzoRate()`
    uint private salary; // Use `picciottiSalary()`

    uint immutable creation_time;
    uint last_salary;

    error GodfatherCantPay(uint min_tokens);

    constructor(uint initialSupply) {
        totalSupply = initialSupply;
        godfather = msg.sender;

        mafiosi[msg.sender] = Mafioso({
            id: msg.sender,
            tokens: initialSupply,
            role: Role.GODFATHER,
            active: true,
            children: 0
        });
        address_users.push(msg.sender);
        salary = 100; // Default initial salary

        creation_time = block.timestamp;
        last_salary = block.timestamp;
    }

    modifier MustBeAMafioso(address account) {
        require(mafiosi[account].id != address(0), "This address is not a 'mafioso'");

        _;
    }

    modifier MustBeTheGodfather() {
        require(msg.sender == godfather, "This action is available only for the godfather.");

        _;
    }

    modifier MustBeAtLeastAPicciotto(address account) {
        require(
            account == godfather || mafiosi[account].role == Role.PICCIOTTO,
            "This action is available only for the godfather and picciottis."
        );

        _;
    }

    function balanceOf(address account) public view override MustBeAMafioso(account) returns (uint256) {
        return mafiosi[account].tokens;
    }

    function _transfer_money(address sender, address recipient, uint amount) internal {
        uint to_godfather = (
            (sender == godfather) ?
            0 : amount - (amount * pizzo / 100)
        );
    
        mafiosi[sender].tokens -= amount;
        mafiosi[recipient].tokens += (amount - to_godfather);
        mafiosi[godfather].tokens += to_godfather;

        emit Transfer(sender, recipient, (amount - to_godfather));
        emit Transfer(recipient, godfather, to_godfather);
    }

    function transfer(address recipient, uint256 amount) 
        public 
        override 
        MustBeAMafioso(recipient) MustBeAMafioso(msg.sender) 
        returns (bool) 
    {
        require(mafiosi[msg.sender].tokens >= amount, "You don't have enough tokens to make this transfer");

        _transfer_money(msg.sender, recipient, amount);

        // Always returns a true
        return true;
    }


    function approve(address spender, uint256 amount)
        public
        override
        MustBeAMafioso(msg.sender) MustBeAMafioso(spender)
        returns (bool)
    {
        approves[spender].push(Approve({
            owner: msg.sender,
            amount: amount
        }));


        emit Approval(msg.sender, spender, amount);

        // Always return a true
        return true;
    }

    function transferFrom(address sender, address recipient, uint256 amount) 
        public 
        override
        MustBeAMafioso(recipient) MustBeAMafioso(sender)
        returns (bool)
    {
        bool sent = false;
        for (uint8 i = 0; i < approves[msg.sender].length; ++i) {
            if (approves[msg.sender][i].owner == sender) {
                if (approves[msg.sender][i].amount >= amount) {  
                    _transfer_money(sender, recipient, amount);
                    approves[msg.sender][i].amount -= amount;
                    sent = true;
                }
            }
            
            if (sent) return true;
        }

        return false;
    }

    function allowance(address owner, address spender) 
        public view 
        override
        returns (uint256)
    {
        uint amount = 0;
        for (uint8 i = 0; i < approves[spender].length; ++i) {
            if (approves[spender][i].owner == owner) {
                amount += approves[spender][i].amount;
            }
        }

        return amount;
    }

    function picciotti() override public view returns (address[] memory) {
        address[] memory _mafiosi_list = new address[](address_users.length);

        uint8 j = 0;

        for (uint8 i = 0; i < address_users.length; ++i) {
            if (mafiosi[address_users[i]].role == Role.PICCIOTTO &&
                mafiosi[address_users[i]].active
            ) {
                _mafiosi_list[j++] = address_users[i];
            }
        }

        return _mafiosi_list;
    }

    function addPicciotto(address id, uint8 children) public override MustBeTheGodfather {
        mafiosi[id] = Mafioso({
            id: id,
            tokens: 0,
            role: Role.PICCIOTTO,
            active: true,
            children: children
        });
        address_users.push(id);
    }

    function removePicciotto(address id) public override MustBeTheGodfather MustBeAMafioso(id) {
        mafiosi[id].active = false;
    }

    function pizzoRate() public view override returns (uint8) {
        return pizzo;
    }

    function setPizzoRate(uint8 rate) public override MustBeTheGodfather {
        require(rate >= 0 && rate <= 100, "You entered not valid value");

        pizzo = rate;
    }

    function forgeNewTokens(uint additionalSupply) public override MustBeTheGodfather {
        require(additionalSupply >= 0, "You entered a negative rate");

        mafiosi[godfather].tokens += additionalSupply;
        totalSupply += additionalSupply;

        /* This event have to me emitted? */
        emit Transfer(address(0), godfather, additionalSupply);
    }


    function stealTokens(address robbed, uint amount)
        public
        override
        MustBeAtLeastAPicciotto(robbed) 
        MustBeAtLeastAPicciotto(msg.sender)
    {
        require(robbed != godfather, "You can't steal tokens from the godfather!");
        require(mafiosi[robbed].tokens >= amount, "Robbed mafioso does not have enough tokens");


        mafiosi[msg.sender].tokens += amount;
        mafiosi[robbed].tokens -= amount;

        emit Transfer(robbed, msg.sender, amount);
    }

    function picciottiSalary() public view override returns (uint) {
        return salary;
    }

    function setPicciottiPerChildSalary(uint amount) public override MustBeTheGodfather {
        require(amount >= 0, "You entered a negative rate");

        salary = amount;
    }

    function triggerMonthlyPicciottiSalary() public override {
        /* Change `30 days` value to test this method. */
        require(block.timestamp >= (last_salary + 30 days), "Already paid.");

        uint need_tokens = 0;

        for (uint8 i = 0; i < address_users.length; ++i) {
            if (mafiosi[address_users[i]].role != Role.GODFATHER &&
                mafiosi[address_users[i]].active
            ) {
                need_tokens += (salary * mafiosi[address_users[i]].children);
            }
        }

        if (mafiosi[godfather].tokens < need_tokens) {
            revert GodfatherCantPay(need_tokens);
        }

        for (uint8 i = 0; i < address_users.length; ++i) {
            if (
                mafiosi[address_users[i]].role != Role.GODFATHER &&
                mafiosi[address_users[i]].active
            ) {
                uint amount = (salary * mafiosi[address_users[i]].children);
                mafiosi[address_users[i]].tokens += amount;
                _transfer_money(godfather, address_users[i], amount);
            }
        }

        mafiosi[godfather].tokens -= need_tokens;

        last_salary = block.timestamp;
    }
}

