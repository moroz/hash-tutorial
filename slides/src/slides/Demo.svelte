<script>
  import CodeSnippet from "../components/CodeSnippet.svelte";
  import Layout from "../components/Layout.svelte";

  const pythonSnippet = `mydic = {
  "foo": 42,
  "bar": 69,
  "baz": 420
}
print(mydic)
# {'foo': 42, 'bar': 69, 'baz': 420}`;

  const rubySnippet = `my_hash = {
  foo: 42,
  bar: 69,
  baz: 420
}
puts my_hash
// {foo: 42, bar: 69, baz: 420}`;

  const goSnippet = `myMap := map[string]int{
  "foo": 42,
  "bar": 69,
  "baz": 420,
}
fmt.Printf("%#v\\n", myMap)
// map[string]int{"bar":69, "baz":420, "foo":42}
`;

  const jsSnippet = `const myObj = {
  foo: 42,
  bar: 69,
  baz: 420,
};
console.log(myObj);
// { foo: 42, bar: 69, baz: 420 }`;
</script>

<Layout title="Hash tables in your area">
  <div
    class="grid grid-cols-2 items-start gap-x-24 grid-rows-2 gap-y-8 my-auto"
  >
    <section>
      <h3>Python has <strong>dictionaries</strong></h3>
      <CodeSnippet language="python" code={pythonSnippet} />
    </section>
    <section>
      <h3>Ruby has <strong>hashes</strong></h3>
      <CodeSnippet language="ruby" code={rubySnippet} />
    </section>
    <section>
      <h3>Go has <strong>maps</strong></h3>
      <CodeSnippet language="go" code={goSnippet} />
    </section>
    <section>
      <h3>JavaScript has <strong>objects</strong></h3>
      <CodeSnippet language="js" code={jsSnippet} />
    </section>
  </div>
</Layout>

<style>
  @reference "../style.css";

  h3 {
    @apply text-4xl leading-loose font-semibold;

    &:has(strong) {
      color: rgba(255, 255, 255, 0.87);
    }

    strong {
      color: white;
    }
  }
</style>
