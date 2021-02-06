<ex2>
{
for $student in doc("university_marks.xml")//libretto
where $student/esami//voto/text()=30
return <student>
    {$student/studente/nome/text()}
    { ' ' }
    {$student/studente/cognome/text()}
    </student>
}
</ex2>

