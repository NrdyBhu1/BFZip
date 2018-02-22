# BFZip
A compression algorithm for Brainfuck

BFZip is a loss(y,less)* compression algorithm for the Brainfuck programming language. It was inspired by User:Aardwolf's proposal on the Esolangs wiki for a [two instruction version of Brainfuck](https://esolangs.org/wiki/Talk:BF_instruction_minimalization). It does this by compressing each command down to 3 bits each.

## Instructions

| Bits  | Instruction |
|:-----:|:----------- |
| `000` | `<`         |
| `001` | `>`         |
| `010` | `+`         |
| `011` | `-`         |
| `100` | `[`         |
| `101` | `]`         |
| `110` | `.`         |
| `111` | `,`         |

This is extremely buggy and it should not be used yet.

*it is lossless in the sense that it preserves every single command, but lossy in the sense that it purges every character that isn't a command
