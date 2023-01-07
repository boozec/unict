package it.dmi.tsdw.petshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import it.dmi.tsdw.petshop.Pet;
import it.dmi.tsdw.petshop.Race;

@Repository
public interface PetRepository extends JpaRepository<Pet, Long>{
    @Query(value = "SELECT p FROM Pet p WHERE race_id = ?1")
    public Race searchRace(Long race_id);

    public Race findByRaceName(String name);

}
