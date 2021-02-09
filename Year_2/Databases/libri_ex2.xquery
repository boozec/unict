let $f := doc("libri.xml")
let $authors := $f//autore

for $author in distinct-values($authors)
let $books := $f//libro[autore=$author]
return <author>
            <name>{ $author }</name>
            <num>{ count($books) }</num>
       </author>
