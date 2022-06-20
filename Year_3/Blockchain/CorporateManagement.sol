/*
    Corso Blockchain e Cryptocurrencies - Compito di laboratorio del 12/07/2021

    Scrivere un contratto `CorporateManagement` che implementi l'interfaccia `CorporateManagementSpecs`
    per la gestione delle decisioni di una società sulla piattaforma Ethereum usando il linguaggio Solidity.

    All'interno della società ci possono essere una serie di soci (associates): il primo è il fondatore che
    crea il contratto stesso con relativa quota (share). Gli altri soci si possono auto-candidare depositando
    una quota sufficiente: tale candidatura viene considerata accettata solo se accettata a maggioranza dai
    soci attuali. Ogni socio può depositare una generica proposta, consistente in una semplice descrizione
    testuale: essa sarà considerata accettata se votata a maggioranza dai soci. Il voto per maggioranza (50% + 1)
    tiene conto del peso della quota in ETH depositata da ogni socio.
    La società, su proposta di qualche socio, può essere anche sciolta purché la risoluzione venga votata 
    all'unanimità.

    Di seguito alcuni dettagli sui singoli elementi obbligatori dell'interfaccia:
    - tutti i casi illustrati sopra vengono considerti come proposte da accettare: le tipologie di proposte 
      corrispondono all'enumerazione `ProposalCategory`;
    - il primo socio (fondatore) crea il contratto specificando la quota minima e versando, contestualmente, la
      propria di quota sufficiente;

    X - il metodo `depositFunds` può essere usato da chiunque per auto-candidarsi a socio, versando la relativa
      sufficiente quota; il metodo può essere usato sia dai soci che da candidati-soci per aumentare la propria 
      quota;
    X - il metodo `voteProposal`, utilizzabile solo dai soci effettivi, può essere usato per aderire, con la propria
      quota, all'accettazione della proposta tramite l'apposito identificativo; ovviamente un socio può votare una
      sola volta per ogni singola proposta, tale metodo dovrà anche verificare se la proposta ha raggiunto i voti 
      necessari e far scaturire i relativi effetti;
    X - i metodi `depositGenericProposal` e `depositDissolutionProposal` permettono, unicamente ai soci, di depositare,
      rispettivamente, una generica proposta con descrizione testuale o una proposta di scioglimento;
    - nel caso in cui una proposta di scioglimento venga accettata all'unanimità la società va in liquidazione e pertanto
      nessuna funzionalità avrà più effetti ad eccezione del metodo `requestShareRefunding` che permette al singolo
      socio di riscuotere la propria quota;
    - i predicati `isAssociated` e `isDissoluted` permettono, rispettivamente, di verificare se un indirizzo specificato
      corrisponde ad un socio effettivo o se la società è in scioglimento;

    - gli eventi di tipo `New...` dovranno essere generati quando una proposta viene creata a seguito di un'azione 
      esterna; depositare dei fondi sufficienti da parte di un non-socio rappresenta una proposta di candidatura;
    - gli eventi di tipo `Accepted....` dovranno essere generati ogniqualvolta una relativa proposta viene accettata;
      notare che all'atto della creazione della società il socio fondatore è implicitamente accettato.
    
    Il contratto dovrà occuparsi di validare gli input ricevuti secondo criteri ovvi di sensatezza.

*/

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;
import "exam.sol";

contract CorporateManagement is CorporateManagementSpecs {
    enum AssociateRole { NONE, CANDIDATE, ASSOCIATE, FOUNDER }
    struct Associate {
        address payable id;
        uint share;
        AssociateRole role;
    }

    struct Proposal {
        ProposalCategory category;
        address owner;
        Associate[] votes;
        string descr;
    }

    uint public minimumShare;
    mapping(address => Associate) associates;
    address[] associateIds;
    address public immutable founder;

    Proposal[] public proposals;

    bool public override isDissoluted = false;

    function isAssociated(address id) external view override returns (bool) {
        if (associates[id].id == address(0)) {
            return false;
        }

        return (associates[id].role == AssociateRole.ASSOCIATE || associates[id].role == AssociateRole.FOUNDER);
    }


    constructor(uint minimumAssociatingShare) payable {
        assert(minimumAssociatingShare == msg.value);
        minimumShare = msg.value;
        associates[msg.sender] = Associate({
            id: payable(msg.sender),
            share: msg.value,
            role: AssociateRole.FOUNDER
        });

        associateIds.push(msg.sender);
        founder = msg.sender; 
    }

    modifier NeedDissolution(bool action) {
        if (!action) {
            require(!isDissoluted, "Can't do this action because the corporate is dissoluting");
        } else {
            require(isDissoluted, "Can't do this action because the corporate is not dissoluting");
        }
        _;
    }
    
    modifier NeedAssociate {
        if (!this.isAssociated(msg.sender)) {
            revert("You must be an associated to vote this proposal.");
        }
        _;
    }

    function depositFunds() external override payable NeedDissolution(false) {
        if (associates[msg.sender].id == address(0)) {
            require(msg.value >= minimumShare, "The share must be at least equals to the minimum");
            associates[msg.sender] = Associate({
                id: payable(msg.sender),
                share: msg.value,
                role: AssociateRole.CANDIDATE
            });
            Proposal storage p = proposals.push();
            p.category = ProposalCategory.NewAssociationAcceptance;
            p.owner = msg.sender;

            emit NewAssociateCandidate(proposals.length-1, p.owner);
        } else {
            associates[msg.sender].share += msg.value;
        }
    }


    function depositGenericProposal(string calldata description) external override NeedDissolution(false) NeedAssociate {
        Proposal storage p = proposals.push();
        p.category = ProposalCategory.Generic;
        p.owner = msg.sender;
        p.descr = description;

        emit NewGenericProposal(proposals.length-1, description);
    }

     
    function depositDissolutionProposal() external override NeedDissolution(false) NeedAssociate {
        Proposal storage p = proposals.push();
        p.category = ProposalCategory.CorporateDissolution;
        p.owner = msg.sender;

        emit NewDissolutionProposal(proposals.length-1);
    }


    function voteProposal(uint proposalId) external override NeedDissolution(false) NeedAssociate {
        Proposal storage p = proposals[proposalId];
        uint totalShare = 0;
        for (uint i = 0; i < p.votes.length; ++i) {
            totalShare += p.votes[i].share;
            if (p.votes[i].id == msg.sender) {
                revert("Already voted this proposal!");
            }
        }
        p.votes.push(associates[msg.sender]);
        totalShare += associates[msg.sender].share;

        uint minQuote = (address(this).balance / 2) + 1;

        if (p.category == ProposalCategory.CorporateDissolution && p.votes.length == associateIds.length) {
            isDissoluted = true;
            emit AcceptedCorporateDissolution();
        } else if (totalShare >= minQuote) {
            if (p.category == ProposalCategory.NewAssociationAcceptance) {
                assert(associates[p.owner].role == AssociateRole.CANDIDATE);
                associateIds.push(p.owner);
                associates[p.owner].role = AssociateRole.ASSOCIATE;
                emit AcceptedAssociate(p.owner);
            } else if (p.category == ProposalCategory.Generic) {
                emit AcceptedGenericProposal(p.descr);
            }
        }
    }


    function requestShareRefunding() external override NeedDissolution(true) {
        if (associates[msg.sender].id == address(0)) {
            revert("You're not one of the associates, can't refund");
        }

        associates[msg.sender].id.transfer(associates[msg.sender].share);
    }
}
