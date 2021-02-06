<ex3>
{
let $f := doc("university_marks.xml")
let $courses := distinct-values($f//materia)

for $course in $courses
return <course area="{$course}">
    {
    for $data in $f//libretto
    where $data//esami//esame//materia/text()=$course
    return <student>{$data//studente/@matricola}</student>
    }
    </course>
}
</ex3>
