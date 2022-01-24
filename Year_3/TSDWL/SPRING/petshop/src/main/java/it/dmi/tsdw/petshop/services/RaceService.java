package it.dmi.tsdw.petshop.services;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import it.dmi.tsdw.petshop.Race;
import it.dmi.tsdw.petshop.repositories.RaceRepository;

@Service
public class RaceService {

    @Autowired
    private RaceRepository repository;

    public Race addRace(Race e) {
        return repository.save(e);
    }

    public Optional<Race> getRace(Long id) {
        return repository.findById(id);
    }

    public List<Race> getAllRaces() {
        List<Race> output = new ArrayList<Race>();
        repository.findAll().forEach(output::add);
        return output;
    }

    public Race updateRace(Race e) {
        return repository.save(e);
    }

    public void deleteRace(Race e) {
        repository.delete(e);
    }

    public void deleteRace(Long id) {
        repository.deleteById(id);
    }
}