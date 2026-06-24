# Search Engine (C++)

A from-scratch information retrieval engine built in C++ over a 50-document Project Gutenberg corpus. Built as a portfolio project demonstrating core IR fundamentals without using any search libraries.

---

## Features

- **Document loader** — reads and strips Gutenberg headers/footers from raw `.txt` files
- **Tokenizer** — lowercases, splits on hyphens, handles UTF-8 safely via `unsigned char` casting
- **Inverted index** — maps every term to a postings list of `(doc_id, position)` pairs
- **TF-IDF scoring** — log-normalized term frequency × inverse document frequency, summed across query terms
- **Top-k retrieval** — returns top N results sorted by score, with deterministic tie-breaking
- **Query parser** — detects keyword queries vs. phrase queries (double-quote syntax)
- **Phrase search** — positional adjacency matching for exact multi-word phrases, arbitrary length
- **Interactive CLI** — query loop with `quit` to exit

---

## How It Works

### Keyword Search
Query terms are tokenized identically to how documents were indexed (same function, called in both paths). Each term's TF-IDF contribution is summed per document. Results are ranked by total score descending.

```
TF-IDF(term, doc) = (1 + log(raw_count)) × log(N / df)
```

- `raw_count` — occurrences of the term in the document
- `N` — total documents in corpus
- `df` — number of documents containing the term

### Phrase Search
Wrap a query in double quotes to search for an exact phrase:
```
"it was the best of times"
```
The engine looks up postings for each token and checks whether they appear at consecutive positions within the same document. A document is returned only if the entire sequence matches adjacently, in order.

Positions are stored in the index at build time — this was a deliberate upfront decision to avoid retrofitting the index later when phrase search was added.

---

## Build

**Requirements:** g++ 13+, CMake 3.16+

```bash
git clone https://github.com/jj761/search-engine-cpp.git
cd search-engine-cpp
mkdir build && cd build
cmake ..
make
```

---

## Usage

```bash
cd build
./search_engine
```

```
Documents loaded: 50
Unique terms in index: 148263

Enter a query (or 'quit' to exit):
> captain ahab
Top 10 results:
  doc 30 (25833.txt)  score 6.23276
  doc 18 (22793.txt)  score 5.09202
  ...

> "it was"
Phrase matches (49 docs):
  doc 0 (16266.txt)
  doc 1 (3891.txt)
  ...

> quit
```

---

## Run Tests

Each component has an isolated test binary:

```bash
./test_tokenizer
./test_corpus_tokenize
./test_scorer
./test_topk
./test_parser
./test_phrase
```

Tests use a print-and-verify approach with hand-calculated expected values. No test framework dependency.

---

## Corpus

50 plain-text books from [Project Gutenberg](https://www.gutenberg.org), excluded from the repo via `.gitignore`. To rebuild the corpus, download `.txt` files into the `corpus/` directory.

**Corpus stats:**
- 50 documents
- 7,202,101 total tokens
- 148,263 unique terms
- Document sizes: 55,557 – 4,063,259 bytes

---

## Project Structure

```
src/
  loader.cpp/h       — document loading and header/footer stripping
  tokenizer.cpp/h    — tokenization and normalization
  indexer.cpp/h      — inverted index construction
  scorer.cpp/h       — TF-IDF scoring
  topk.cpp/h         — top-k retrieval with tie-breaking
  parser.cpp/h       — query parsing and phrase detection
  phrase.cpp/h       — phrase search via positional adjacency
  main.cpp           — interactive query loop
tests/
  test_tokenizer.cpp
  test_corpus_tokenize.cpp
  test_scorer.cpp
  test_topk.cpp
  test_parser.cpp
  test_phrase.cpp
```

---

## Built in ~12 hours across 6 days.
