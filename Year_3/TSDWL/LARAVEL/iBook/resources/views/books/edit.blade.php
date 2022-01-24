@extends('layout')

@section('content')
<h1>Edit `{{ $book->name }}`</h1>

<form method="post" action="/books/<?php echo $book->id; ?>">
    @csrf
    @method('put')
    <div>
        <label for="name">Name: </label>
        <input type="text" name="name" id="name" required value="<?php echo $book->name; ?>">
    </div>
    <div>
        <label for="published_at">Published at: </label>
        <input type="datetime" name="published_at" id="published_at" value="<?php echo $book->published_at; ?>">
    </div>
    <div>
        <label for="is_online">Is online?: </label>
        <input type="checkbox" name="is_online" id="is_online" <?php echo ($book->is_online ? 'checked': ''); ?>>
    </div>
    <div>
        <label for="author_id">Author: </label>
        <select id="author_id" name="author_id">
            <option value="">Select an author</option>
            @foreach ($authors as $author)
            <option value="{{ $author->id }}" <?php if($author->id == $book->author_id) { echo 'selected';
                                              } ?>>
{{ $author->name }}</option>
            @endforeach
        </select>
    </div>
    <button type="submit">Save</button>
</form>
@endsection
