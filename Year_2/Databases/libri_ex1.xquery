for $libri in doc("libri.xml")//libro
return count($libri//capitolo)
