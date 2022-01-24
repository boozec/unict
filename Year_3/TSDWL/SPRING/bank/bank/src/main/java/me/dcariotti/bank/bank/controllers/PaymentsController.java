package me.dcariotti.bank.bank.controllers;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import me.dcariotti.bank.bank.Payments;
import me.dcariotti.bank.bank.servicies.PaymentsService;

@RestController
@RequestMapping("/api")
public class PaymentsController {

    @Autowired
    private PaymentsService service;

    @GetMapping("/payments")
    public ResponseEntity<List<Payments>> getAllPaymentss() {
        List<Payments> entityList = service.getAllPaymentss();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/payments/{id}")
    public ResponseEntity<Payments> getPayments(@PathVariable long id) {
        Optional<Payments> entity = service.getPayments(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/payments")
    public ResponseEntity<Payments> addPayments(@Valid @RequestBody Payments e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Payments entity = service.addPayments(e);
        return ResponseEntity.created(new URI("/payments/resourcePath" + entity.getId())).body(entity);
    }

    @PutMapping("/edit")
    public ResponseEntity<Payments> updatePayments(@Valid @RequestBody Payments e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Payments entity = service.updatePayments(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/delete/{id}")
    public ResponseEntity<Void> deletePayments(@PathVariable long id) {
        if (service.getPayments(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deletePayments(id);
        return ResponseEntity.ok().build();
    }
}