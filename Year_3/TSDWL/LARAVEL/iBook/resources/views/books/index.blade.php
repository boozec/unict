@extends('layout')

@section('content')

<h1>Hello world! They're my books:</h1>
@foreach ($books as $book)
<p>
    <a href="/books/{{ $book->id }}">{{ $book->name }}</a>
    @if ($book->author_id)
    <span>by {{ $book->author->name }}</span>
    @endif
</p>
@endforeach

@endsection
