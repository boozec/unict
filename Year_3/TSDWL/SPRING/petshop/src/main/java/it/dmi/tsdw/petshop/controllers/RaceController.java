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

import it.dmi.tsdw.petshop.Race;
import it.dmi.tsdw.petshop.services.RaceService;

@RestController
@RequestMapping("/api")
public class RaceController {

    @Autowired
    private RaceService service;

    @GetMapping("/races")
    public ResponseEntity<List<Race>> getAllRaces() {
        List<Race> entityList = service.getAllRaces();
        return ResponseEntity.ok(entityList);
    }

    @GetMapping("/races/{id}")
    public ResponseEntity<Race> getRace(@PathVariable long id) {
        Optional<Race> entity = service.getRace(id);
        if(entity.isPresent())
            return ResponseEntity.ok(entity.get());
        else
            return ResponseEntity.notFound().build();
    }

    @PostMapping("/races")
    public ResponseEntity<Race> addRace(@Valid @RequestBody Race e) throws URISyntaxException {
        if (e.getId() != null) {
            return ResponseEntity.badRequest().build();
        }
        Race entity = service.addRace(e);
        return ResponseEntity.created(new URI("/api/races" + entity.getId())).body(entity);
    }

    @PutMapping("/races")
    public ResponseEntity<Race> updateRace(@Valid @RequestBody Race e) {
        if (e.getId() == null)
            return ResponseEntity.notFound().build();
        Race entity = service.updateRace(e);
        return ResponseEntity.ok(entity);
    }

    @DeleteMapping("/races/{id}")
    public ResponseEntity<Void> deleteRace(@PathVariable long id) {
        if (service.getRace(id).isEmpty())
            return ResponseEntity.notFound().build();

        service.deleteRace(id);
        return ResponseEntity.ok().build();
    }
}