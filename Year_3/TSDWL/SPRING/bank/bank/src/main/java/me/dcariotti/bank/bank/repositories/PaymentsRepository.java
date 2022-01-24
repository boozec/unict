package me.dcariotti.bank.bank.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import me.dcariotti.bank.bank.Payments;

@Repository
public interface PaymentsRepository extends JpaRepository<Payments, Long>{}