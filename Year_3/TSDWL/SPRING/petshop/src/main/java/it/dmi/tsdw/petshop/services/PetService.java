package it.dmi.tsdw.petshop.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import it.dmi.tsdw.petshop.Pet;
import it.dmi.tsdw.petshop.repositories.PetRepository;

@Service
public class PetService {

    @Autowired
    private PetRepository repository;

    public Pet addPet(Pet e) {
        return repository.save(e);
    }

    public Optional<Pet> getPet(Long id) {
        return repository.findById(id);
    }

    public List<Pet> getAllPets() {
        List<Pet> output = new ArrayList<Pet>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Pet updatePet(Pet e) {
        return repository.save(e);
    }

    public void deletePet(Pet e) {
        repository.delete(e);
}

    public void deletePet(Long id) {
        repository.deleteById(id);
    }
}