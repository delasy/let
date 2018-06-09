describe 'Let grammar', ->
  grammar = null

  beforeEach ->
    waitsForPromise ->
      atom.packages.activatePackage('let')

    runs ->
      grammar = atom.syntax.grammarForScopeName('source.let')

  it 'parses the grammar', ->
    expect(grammar).toBeTruthy()
    expect(grammar.scopeName).toBe 'source.let'
