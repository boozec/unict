package it.dmi.tsdw.petshop.controllers;

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

import it.dmi.tsdw.petshop.Pet;
import it.dmi.tsdw.petshop.services.PetService;

@RestController
@RequestMapping("/api")
public class PetController {

    @Autowired
    private PetService service;

    @GetMapping("/pets")
    public ResponseEntity<List<Pet>> getAllPets() {
        List<Pet> entityList = service.getAllPets();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/pets/{id}")
    public ResponseEntity<Pet> getPet(@PathVariable long id) {
        Optional<Pet> entity = service.getPet(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/pets")
    public ResponseEntity<Pet> addPet(@Valid @RequestBody Pet e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Pet entity = service.addPet(e);
        return ResponseEntity.created(new URI("/api/resourcePath" + entity.getId())).body(entity);
    }

    @PutMapping("/pets")
    public ResponseEntity<Pet> updatePet(@Valid @RequestBody Pet e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Pet entity = service.updatePet(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/pets/{id}")
    public ResponseEntity<Void> deletePet(@PathVariable long id) {
        if (service.getPet(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deletePet(id);
        return ResponseEntity.ok().build();
    }
}