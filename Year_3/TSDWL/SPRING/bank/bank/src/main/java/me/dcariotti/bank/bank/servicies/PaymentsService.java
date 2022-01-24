package me.dcariotti.bank.bank.servicies;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import me.dcariotti.bank.bank.Payments;
import me.dcariotti.bank.bank.repositories.PaymentsRepository;

@Service
public class PaymentsService {

    @Autowired
    private PaymentsRepository repository;

    public Payments addPayments(Payments e) {
        return repository.save(e);
    }

    public Optional<Payments> getPayments(Long id) {
        return repository.findById(id);
    }

    public List<Payments> getAllPaymentss() {
        List<Payments> output = new ArrayList<Payments>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Payments updatePayments(Payments e) {
        return repository.save(e);
    }

    public void deletePayments(Payments e) {
        repository.delete(e);
}

    public void deletePayments(Long id) {
        repository.deleteById(id);
    }
}