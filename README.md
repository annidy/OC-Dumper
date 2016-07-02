#OC-Dumper

OC-Dumper is a utility I used to got print `NSData` from log

```
➜  OC-Dumper ./dump < test.txt
68 65 6c 6c 6f 20 77 6f 72 6c 64 21 0a          | hello world!.
Length: 13
68 65 6c 6c 6f 20 77 6f 72 6c 64 21 0a          | hello world!.
Length: 13
```

it's automatic ignore non `NSData` value.

also, sometime I need generate some `NSData` to set in xcode Watch Console

```
➜  OC-Dumper ./dump test.txt  
<74657374 2031203c 36383635 36633663 20366632 30373736 66203732 36633634 32312030 613e2020 20202020 20202020 200a7465 73742032 207b3078 36382c30 7836352c 30783663 2c307836 632c2030 7836662c 30783230 2c307837 372c3078 36662c20 30783732 2c307836 632c3078 36342c30 7832312c 20307830 617d>
```