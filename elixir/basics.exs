IO.puts 1 # int
IO.puts 1.0 # float
IO.puts true # boolean
IO.puts :symbol # symbol/atom
IO.puts "String" # string
[1,2,3] # list
{1,2,3,4} # tuple

IO.puts "binary, octal, hexa:"
IO.puts 0b1010 # binary
IO.puts 0o777  # octal
IO.puts 0x1F   # hexadecimal

# basic arithmetic
IO.puts "Arithmetics results:"
IO.puts 1 + 2
IO.puts 9 / 3
IO.puts div(10,2)
IO.puts rem 10, 3

IO.puts round 3.99
IO.puts trunc 3.78
IO.puts true == false

# Boolean
IO.puts is_boolean(true)
IO.puts is_boolean(1)
IO.puts is_integer(190)
IO.puts is_integer(190.1)
IO.puts is_number(190)
IO.puts is_number(190.1)
IO.puts is_float(190.1)

IO.puts 1 == 1.0
IO.puts 1 === 1.0

# Atoms
IO.puts :atom
IO.puts is_atom(:atom)

# String
IO.puts "Unicode String रोहित   "
IO.puts "hellö #{:world}"
IO.puts "hello\nworld"

IO.puts is_binary("All things in Elixir")
IO.puts byte_size("Rohit")
IO.puts String.length("testing123")
IO.puts String.upcase("rohit")

IO.puts "String " <> "concatenation"

# Anonymous function
add = fn a,b -> a + b end
IO.puts is_function(add)
IO.puts add.(1,2)
add_two = fn a -> add.(a, 2) end # closure
IO.puts add_two.(10)

# Linked List
[1, 2, true, 3]
length [1, 2, 3]
[1, 2, 3] ++ [4, 5, 6]
[1, true, 2, false, 3, true] -- [true, false]

list = [1,2,3]
IO.puts hd(list) # head
IO.puts tl(list) # tail
IO.puts [104, 101, 108, 108, 111]

IO.puts 'hello' == "hello" # single quotes != double quotes

# Tuples
{:ok, "hello"}
tuple_size {:ok, "hello"}

tuple = {:ok, "hello"}

IO.puts elem(tuple, 1)
tuple_size(tuple)

new_tuple = put_elem(tuple, 1, "world") # immutable tuple, returns a new tuple

IO.puts new_tuple == tuple

list = [1|[2|[3|[]]]]
[0] ++ list
list ++ [4]

# file reading
content = File.read("./hello.exs")
IO.puts elem(content, 1)

# Pattern matching
x = 1
1 = x # = used as match operator
{a, b, c} = {:hello, "world", 42}
{:ok, result} = {:ok, 13} # match operation
[head | tail] = [1, 2, 3]

# Pinning
x = 1
x = 2 # valid re-assignment

x = 1
^x = 1 # pin to matching to prior value instead of re-assignment
{x, ^x} = {2, 1}

# unused var/tail here
[h | _] = [1, 2, 3]
IO.puts h
