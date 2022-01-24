@extends('layout')

@section('content')
<h1>Create a new book</h1>

<form method="post" action="/books">
    @csrf
    <div>
        <label for="name">Name: </label>
        <input type="text" name="name" id="name">
    </div>
    <div>
        <label for="published_at">Published at: </label>
        <input type="date" name="published_at" id="published_at">
    </div>
    <div>
        <label for="is_online">Is online?: </label>
        <input type="checkbox" name="is_online" id="is_online">
    </div>
    <div>
        <label for="author_id">Author: </label>
        <input type="text" name="name" id="name">
    </div>
</form>

@endsection
