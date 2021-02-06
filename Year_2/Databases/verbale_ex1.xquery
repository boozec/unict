<ex1>
{
let $f := doc("verbale.xml")
for $verbale in $f//verbale
where $verbale/studente[@cdl="667"] and $verbale/esame/materia/text()="Reti di Calcolatori"
return <voto>
    <valore>
    {
    $verbale/esame/voto/text()
    }
    </valore>
    {if ($verbale/esame/lode) then (
    <lode>Y</lode>
    ) else () }
    </voto>

}
</ex1>
