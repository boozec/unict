package it.dmi.tsdw.petshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import it.dmi.tsdw.petshop.Race;

@Repository
public interface RaceRepository extends JpaRepository<Race, Long>{
}