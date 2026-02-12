# SGPR

Projeto de controle de despesas e rateio usado nas atividades do curso.

**Visão rápida**
- Implementações em duas variações de estrutura: `estrutura_base` e `estrutura_basePattern`.
- A versão `estrutura_basePattern` aplica padrões de projeto: Factory, Strategy e Repository.

**Onde olhar**
- Código fonte principal: [estrutura_basePattern/src](estrutura_basePattern/src)
- Fabrica: [estrutura_basePattern/src/lib/infra/factory/Factory.h](estrutura_basePattern/src/lib/infra/factory/Factory.h)
- Strategy (rateio): [estrutura_basePattern/src/lib/domain/RateioStrategy.h](estrutura_basePattern/src/lib/domain/RateioStrategy.h)
- Repository (despesas): [estrutura_basePattern/src/lib/infra/repository/IDespesaRepository.h](estrutura_basePattern/src/lib/infra/repository/IDespesaRepository.h)

**Padrões de projeto usados**
- Factory: centraliza criação de `ServicoDespesas`, `ServicoRateio` e repositórios (veja `infra/factory`).
- Strategy: interface `RateioStrategy` com implementação `EqualRateio` para cálculo do rateio.
- Repository: interface `IDespesaRepository` com implementação em memória `InMemoryDespesaRepository`.

**Como compilar (WSL / Linux)**
1. Entre na pasta desejada (ex.: `estrutura_basePattern`):

```bash
cd estrutura_basePattern
make
```

2. Os binários gerados ficam em `estrutura_basePattern/bin` (`app`, `func_teste`, `unit_teste`).

**Como executar**
- Executar a aplicação:

```bash
./bin/app
```

- Executar testes unitários:

```bash
./bin/unit_teste
```

**Estrutura do projeto (resumida)**
- `src/lib/domain` — entidades e estratégias (`Despesa`, `Usuario`, `Rateio`, `RateioStrategy`, `EqualRateio`).
- `src/lib/infra/factory` — fábricas para criar serviços e repositórios.
- `src/lib/infra/repository` — interfaces e implementações de repositório (`IDespesaRepository`, `InMemoryDespesaRepository`).
- `src/lib/services` — serviços que usam repositórios e estratégias (`ServicoDespesas`, `ServicoRateio`, `ServicoExtrato`).
- `tests` — testes funcionais e unitários demonstrando uso dos serviços.

**Dependências**
- Compilador C++ (g++), `make`.

