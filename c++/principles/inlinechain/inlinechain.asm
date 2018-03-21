00000000  7F45              jg 0x47
00000002  4C                dec sp
00000003  46                inc si
00000004  0101              add [bx+di],ax
00000006  0100              add [bx+si],ax
00000008  0000              add [bx+si],al
0000000A  0000              add [bx+si],al
0000000C  0000              add [bx+si],al
0000000E  0000              add [bx+si],al
00000010  0200              add al,[bx+si]
00000012  0300              add ax,[bx+si]
00000014  0100              add [bx+si],ax
00000016  0000              add [bx+si],al
00000018  40                inc ax
00000019  8404              test [si],al
0000001B  0834              or [si],dh
0000001D  0000              add [bx+si],al
0000001F  00980900          add [bx+si+0x9],bl
00000023  0000              add [bx+si],al
00000025  0000              add [bx+si],al
00000027  0034              add [si],dh
00000029  0020              add [bx+si],ah
0000002B  0008              add [bx+si],cl
0000002D  0028              add [bx+si],ch
0000002F  001D              add [di],bl
00000031  001A              add [bp+si],bl
00000033  00060000          add [0x0],al
00000037  0034              add [si],dh
00000039  0000              add [bx+si],al
0000003B  0034              add [si],dh
0000003D  800408            add byte [si],0x8
00000040  3480              xor al,0x80
00000042  0408              add al,0x8
00000044  0001              add [bx+di],al
00000046  0000              add [bx+si],al
00000048  0001              add [bx+di],al
0000004A  0000              add [bx+si],al
0000004C  050000            add ax,0x0
0000004F  0004              add [si],al
00000051  0000              add [bx+si],al
00000053  0003              add [bp+di],al
00000055  0000              add [bx+si],al
00000057  0034              add [si],dh
00000059  0100              add [bx+si],ax
0000005B  0034              add [si],dh
0000005D  81040834          add word [si],0x3408
00000061  81040813          add word [si],0x1308
00000065  0000              add [bx+si],al
00000067  0013              add [bp+di],dl
00000069  0000              add [bx+si],al
0000006B  0004              add [si],al
0000006D  0000              add [bx+si],al
0000006F  0001              add [bx+di],al
00000071  0000              add [bx+si],al
00000073  0001              add [bx+di],al
00000075  0000              add [bx+si],al
00000077  0000              add [bx+si],al
00000079  0000              add [bx+si],al
0000007B  0000              add [bx+si],al
0000007D  800408            add byte [si],0x8
00000080  00800408          add [bx+si+0x804],al
00000084  7C06              jl 0x8c
00000086  0000              add [bx+si],al
00000088  7C06              jl 0x90
0000008A  0000              add [bx+si],al
0000008C  050000            add ax,0x0
0000008F  0000              add [bx+si],al
00000091  1000              adc [bx+si],al
00000093  0001              add [bx+di],al
00000095  0000              add [bx+si],al
00000097  007C06            add [si+0x6],bh
0000009A  0000              add [bx+si],al
0000009C  7C96              jl 0x34
0000009E  0408              add al,0x8
000000A0  7C96              jl 0x38
000000A2  0408              add al,0x8
000000A4  2801              sub [bx+di],al
000000A6  0000              add [bx+si],al
000000A8  3001              xor [bx+di],al
000000AA  0000              add [bx+si],al
000000AC  06                push es
000000AD  0000              add [bx+si],al
000000AF  0000              add [bx+si],al
000000B1  1000              adc [bx+si],al
000000B3  0002              add [bp+si],al
000000B5  0000              add [bx+si],al
000000B7  00940600          add [si+0x6],dl
000000BB  00949604          add [si+0x496],dl
000000BF  08949604          or [si+0x496],dl
000000C3  08E0              or al,ah
000000C5  0000              add [bx+si],al
000000C7  00E0              add al,ah
000000C9  0000              add [bx+si],al
000000CB  00060000          add [0x0],al
000000CF  0004              add [si],al
000000D1  0000              add [bx+si],al
000000D3  0004              add [si],al
000000D5  0000              add [bx+si],al
000000D7  004801            add [bx+si+0x1],cl
000000DA  0000              add [bx+si],al
000000DC  48                dec ax
000000DD  81040848          add word [si],0x4808
000000E1  81040820          add word [si],0x2008
000000E5  0000              add [bx+si],al
000000E7  0020              add [bx+si],ah
000000E9  0000              add [bx+si],al
000000EB  0004              add [si],al
000000ED  0000              add [bx+si],al
000000EF  0004              add [si],al
000000F1  0000              add [bx+si],al
000000F3  0050E5            add [bx+si-0x1b],dl
000000F6  7464              jz 0x15c
000000F8  28060000          sub [0x0],al
000000FC  28860408          sub [bp+0x804],al
00000100  28860408          sub [bp+0x804],al
00000104  1400              adc al,0x0
00000106  0000              add [bx+si],al
00000108  1400              adc al,0x0
0000010A  0000              add [bx+si],al
0000010C  0400              add al,0x0
0000010E  0000              add [bx+si],al
00000110  0400              add al,0x0
00000112  0000              add [bx+si],al
00000114  51                push cx
00000115  E574              in ax,0x74
00000117  640000            add [fs:bx+si],al
0000011A  0000              add [bx+si],al
0000011C  0000              add [bx+si],al
0000011E  0000              add [bx+si],al
00000120  0000              add [bx+si],al
00000122  0000              add [bx+si],al
00000124  0000              add [bx+si],al
00000126  0000              add [bx+si],al
00000128  0000              add [bx+si],al
0000012A  0000              add [bx+si],al
0000012C  06                push es
0000012D  0000              add [bx+si],al
0000012F  0004              add [si],al
00000131  0000              add [bx+si],al
00000133  002F              add [bx],ch
00000135  6C                insb
00000136  69622F6C64        imul sp,[bp+si+0x2f],word 0x646c
0000013B  2D6C69            sub ax,0x696c
0000013E  6E                outsb
0000013F  7578              jnz 0x1b9
00000141  2E736F            cs jnc 0x1b3
00000144  2E3200            xor al,[cs:bx+si]
00000147  0004              add [si],al
00000149  0000              add [bx+si],al
0000014B  0010              add [bx+si],dl
0000014D  0000              add [bx+si],al
0000014F  0001              add [bx+di],al
00000151  0000              add [bx+si],al
00000153  00474E            add [bx+0x4e],al
00000156  55                push bp
00000157  0000              add [bx+si],al
00000159  0000              add [bx+si],al
0000015B  0002              add [bp+si],al
0000015D  0000              add [bx+si],al
0000015F  0002              add [bp+si],al
00000161  0000              add [bx+si],al
00000163  0005              add [di],al
00000165  0000              add [bx+si],al
00000167  0003              add [bp+di],al
00000169  0000              add [bx+si],al
0000016B  0009              add [bx+di],cl
0000016D  0000              add [bx+si],al
0000016F  0008              add [bx+si],cl
00000171  0000              add [bx+si],al
00000173  0003              add [bp+di],al
00000175  0000              add [bx+si],al
00000177  0004              add [si],al
00000179  0000              add [bx+si],al
0000017B  0000              add [bx+si],al
0000017D  0000              add [bx+si],al
0000017F  0000              add [bx+si],al
00000181  0000              add [bx+si],al
00000183  0001              add [bx+di],al
00000185  0000              add [bx+si],al
00000187  0002              add [bp+si],al
00000189  0000              add [bx+si],al
0000018B  0000              add [bx+si],al
0000018D  0000              add [bx+si],al
0000018F  0000              add [bx+si],al
00000191  0000              add [bx+si],al
00000193  0005              add [di],al
00000195  0000              add [bx+si],al
00000197  00060000          add [0x0],al
0000019B  0007              add [bx],al
0000019D  0000              add [bx+si],al
0000019F  0000              add [bx+si],al
000001A1  0000              add [bx+si],al
000001A3  0000              add [bx+si],al
000001A5  0000              add [bx+si],al
000001A7  0000              add [bx+si],al
000001A9  0000              add [bx+si],al
000001AB  0000              add [bx+si],al
000001AD  0000              add [bx+si],al
000001AF  0025              add [di],ah
000001B1  0000              add [bx+si],al
000001B3  0000              add [bx+si],al
000001B5  0000              add [bx+si],al
000001B7  00BC0500          add [si+0x5],bh
000001BB  0012              add [bp+si],dl
000001BD  0000              add [bx+si],al
000001BF  009A0000          add [bp+si+0x0],bl
000001C3  0000              add [bx+si],al
000001C5  0000              add [bx+si],al
000001C7  003C              add [si],bh
000001C9  0000              add [bx+si],al
000001CB  0012              add [bp+si],dl
000001CD  0000              add [bx+si],al
000001CF  00B60000          add [bp+0x0],dh
000001D3  0000              add [bx+si],al
000001D5  0000              add [bx+si],al
000001D7  00DD              add ch,bl
000001D9  0000              add [bx+si],al
000001DB  0012              add [bp+si],dl
000001DD  0000              add [bx+si],al
000001DF  00A70000          add [bx+0x0],ah
000001E3  0024              add [si],ah
000001E5  8604              xchg al,[si]
000001E7  0804              or [si],al
000001E9  0000              add [bx+si],al
000001EB  0011              add [bx+di],dl
000001ED  000E0055          add [0x5500],cl
000001F1  0000              add [bx+si],al
000001F3  0000              add [bx+si],al
000001F5  0000              add [bx+si],al
000001F7  0000              add [bx+si],al
000001F9  0000              add [bx+si],al
000001FB  0020              add [bx+si],ah
000001FD  0000              add [bx+si],al
000001FF  0010              add [bx+si],dl
00000201  0000              add [bx+si],al
00000203  0020              add [bx+si],ah
00000205  8404              test [si],al
00000207  083D              or [di],bh
00000209  0400              add al,0x0
0000020B  0012              add [bp+si],dl
0000020D  0000              add [bx+si],al
0000020F  003D              add [di],bh
00000211  0000              add [bx+si],al
00000213  0000              add [bx+si],al
00000215  0000              add [bx+si],al
00000217  009C0000          add [si+0x0],bl
0000021B  0012              add [bp+si],dl
0000021D  0000              add [bx+si],al
0000021F  006900            add [bx+di+0x0],ch
00000222  0000              add [bx+si],al
00000224  0000              add [bx+si],al
00000226  0000              add [bx+si],al
00000228  0000              add [bx+si],al
0000022A  0000              add [bx+si],al
0000022C  2000              and [bx+si],al
0000022E  0000              add [bx+si],al
00000230  006C69            add [si+0x69],ch
00000233  627374            bound si,[bp+di+0x74]
00000236  64632B            arpl [fs:bp+di],bp
00000239  2B2E736F          sub bp,[0x6f73]
0000023D  2E36005F5F        add [ss:bx+0x5f],bl
00000242  677878            a32 js 0x2bd
00000245  5F                pop di
00000246  7065              jo 0x2ad
00000248  7273              jc 0x2bd
0000024A  6F                outsw
0000024B  6E                outsb
0000024C  61                popa
0000024D  6C                insb
0000024E  6974795F76        imul si,[si+0x79],word 0x765f
00000253  3000              xor [bx+si],al
00000255  5F                pop di
00000256  5A                pop dx
00000257  4E                dec si
00000258  53                push bx
00000259  7438              jz 0x293
0000025B  696F735F62        imul bp,[bx+0x73],word 0x625f
00000260  61                popa
00000261  7365              jnc 0x2c8
00000263  3449              xor al,0x49
00000265  6E                outsb
00000266  6974433145        imul si,[si+0x43],word 0x4531
0000026B  7600              jna 0x26d
0000026D  5F                pop di
0000026E  5A                pop dx
0000026F  4E                dec si
00000270  53                push bx
00000271  7438              jz 0x2ab
00000273  696F735F62        imul bp,[bx+0x73],word 0x625f
00000278  61                popa
00000279  7365              jnc 0x2e0
0000027B  3449              xor al,0x49
0000027D  6E                outsb
0000027E  6974443145        imul si,[si+0x44],word 0x4531
00000283  7600              jna 0x285
00000285  5F                pop di
00000286  4A                dec dx
00000287  765F              jna 0x2e8
00000289  52                push dx
0000028A  65676973746572    imul si,[gs:ebx+0x74],word 0x7265
00000291  43                inc bx
00000292  6C                insb
00000293  61                popa
00000294  7373              jnc 0x309
00000296  657300            gs jnc 0x299
00000299  5F                pop di
0000029A  5F                pop di
0000029B  676D              a32 insw
0000029D  6F                outsw
0000029E  6E                outsb
0000029F  5F                pop di
000002A0  7374              jnc 0x316
000002A2  61                popa
000002A3  7274              jc 0x319
000002A5  5F                pop di
000002A6  5F                pop di
000002A7  006C69            add [si+0x69],ch
000002AA  626D2E            bound bp,[di+0x2e]
000002AD  736F              jnc 0x31e
000002AF  2E36006C69        add [ss:si+0x69],ch
000002B4  626763            bound sp,[bx+0x63]
000002B7  635F73            arpl [bx+0x73],bx
000002BA  2E736F            cs jnc 0x32c
000002BD  2E3100            xor [cs:bx+si],ax
000002C0  6C                insb
000002C1  6962632E73        imul sp,[bp+si+0x63],word 0x732e
000002C6  6F                outsw
000002C7  2E36005F5F        add [ss:bx+0x5f],bl
000002CC  637861            arpl [bx+si+0x61],di
000002CF  5F                pop di
000002D0  61                popa
000002D1  7465              jz 0x338
000002D3  7869              js 0x33e
000002D5  7400              jz 0x2d7
000002D7  5F                pop di
000002D8  49                dec cx
000002D9  4F                dec di
000002DA  5F                pop di
000002DB  7374              jnc 0x351
000002DD  64696E5F7573      imul bp,[fs:bp+0x5f],word 0x7375
000002E3  6564005F5F        add [fs:bx+0x5f],bl
000002E8  6C                insb
000002E9  6962635F73        imul sp,[bp+si+0x63],word 0x735f
000002EE  7461              jz 0x351
000002F0  7274              jc 0x366
000002F2  5F                pop di
000002F3  6D                insw
000002F4  61                popa
000002F5  696E00474C        imul bp,[bp+0x0],word 0x4c47
000002FA  49                dec cx
000002FB  42                inc dx
000002FC  43                inc bx
000002FD  5F                pop di
000002FE  322E3000          xor ch,[0x30]
00000302  47                inc di
00000303  4C                dec sp
00000304  49                dec cx
00000305  42                inc dx
00000306  43                inc bx
00000307  5F                pop di
00000308  322E312E          xor ch,[0x2e31]
0000030C  3300              xor ax,[bx+si]
0000030E  43                inc bx
0000030F  58                pop ax
00000310  58                pop ax
00000311  41                inc cx
00000312  42                inc dx
00000313  49                dec cx
00000314  5F                pop di
00000315  312E3300          xor [0x33],bp
00000319  47                inc di
0000031A  4C                dec sp
0000031B  49                dec cx
0000031C  42                inc dx
0000031D  43                inc bx
0000031E  58                pop ax
0000031F  58                pop ax
00000320  5F                pop di
00000321  332E3400          xor bp,[0x34]
00000325  0000              add [bx+si],al
00000327  0002              add [bp+si],al
00000329  0003              add [bp+di],al
0000032B  0004              add [si],al
0000032D  0001              add [bx+di],al
0000032F  0000              add [bx+si],al
00000331  0005              add [di],al
00000333  0002              add [bp+si],al
00000335  0000              add [bx+si],al
00000337  0001              add [bx+di],al
00000339  0002              add [bp+si],al
0000033B  00900000          add [bx+si+0x0],dl
0000033F  0010              add [bx+si],dl
00000341  0000              add [bx+si],al
00000343  0030              add [bx+si],dh
00000345  0000              add [bx+si],al
00000347  0010              add [bx+si],dl
00000349  69690D0000        imul bp,[bx+di+0xd],word 0x0
0000034E  0400              add al,0x0
00000350  C8000000          enter 0x0,0x0
00000354  1000              adc [bx+si],al
00000356  0000              add [bx+si],al
00000358  731F              jnc 0x379
0000035A  69090000          imul cx,[bx+di],word 0x0
0000035E  0300              add ax,[bx+si]
00000360  D200              rol byte [bx+si],cl
00000362  0000              add [bx+si],al
00000364  0000              add [bx+si],al
00000366  0000              add [bx+si],al
00000368  0100              add [bx+si],ax
0000036A  0200              add al,[bx+si]
0000036C  0100              add [bx+si],ax
0000036E  0000              add [bx+si],al
00000370  1000              adc [bx+si],al
00000372  0000              add [bx+si],al
00000374  0000              add [bx+si],al
00000376  0000              add [bx+si],al
00000378  D3AF6B05          shr word [bx+0x56b],cl
0000037C  0000              add [bx+si],al
0000037E  0500DE            add ax,0xde00
00000381  0000              add [bx+si],al
00000383  0010              add [bx+si],dl
00000385  0000              add [bx+si],al
00000387  007429            add [si+0x29],dh
0000038A  92                xchg ax,dx
0000038B  0800              or [bx+si],al
0000038D  0002              add [bp+si],al
0000038F  00E9              add cl,ch
00000391  0000              add [bx+si],al
00000393  0000              add [bx+si],al
00000395  0000              add [bx+si],al
00000397  007497            add [si-0x69],dh
0000039A  0408              add al,0x8
0000039C  06                push es
0000039D  0800              or [bx+si],al
0000039F  00849704          add [si+0x497],al
000003A3  0807              or [bx],al
000003A5  0100              add [bx+si],ax
000003A7  00889704          add [bx+si+0x497],cl
000003AB  0807              or [bx],al
000003AD  0200              add al,[bx+si]
000003AF  008C9704          add [si+0x497],cl
000003B3  0807              or [bx],al
000003B5  0300              add ax,[bx+si]
000003B7  00909704          add [bx+si+0x497],dl
000003BB  0807              or [bx],al
000003BD  06                push es
000003BE  0000              add [bx+si],al
000003C0  94                xchg ax,sp
000003C1  97                xchg ax,di
000003C2  0408              add al,0x8
000003C4  07                pop es
000003C5  07                pop es
000003C6  0000              add [bx+si],al
000003C8  55                push bp
000003C9  89E5              mov bp,sp
000003CB  83EC08            sub sp,byte +0x8
000003CE  E89100            call 0x462
000003D1  0000              add [bx+si],al
000003D3  E8E400            call 0x4ba
000003D6  0000              add [bx+si],al
000003D8  E80302            call 0x5de
000003DB  0000              add [bx+si],al
000003DD  C9                leave
000003DE  C3                ret
000003DF  00FF              add bh,bh
000003E1  357C97            xor ax,0x977c
000003E4  0408              add al,0x8
000003E6  FF25              jmp near [di]
000003E8  8097040800        adc byte [bx+0x804],0x0
000003ED  0000              add [bx+si],al
000003EF  00FF              add bh,bh
000003F1  258497            and ax,0x9784
000003F4  0408              add al,0x8
000003F6  680000            push word 0x0
000003F9  0000              add [bx+si],al
000003FB  E9E0FF            jmp 0x3de
000003FE  FF                db 0xFF
000003FF  FF                db 0xFF
00000400  FF25              jmp near [di]
00000402  88970408          mov [bx+0x804],dl
00000406  680800            push word 0x8
00000409  0000              add [bx+si],al
0000040B  E9D0FF            jmp 0x3de
0000040E  FF                db 0xFF
0000040F  FF                db 0xFF
00000410  FF25              jmp near [di]
00000412  8C970408          mov [bx+0x804],ss
00000416  681000            push word 0x10
00000419  0000              add [bx+si],al
0000041B  E9C0FF            jmp 0x3de
0000041E  FF                db 0xFF
0000041F  FF                db 0xFF
00000420  FF25              jmp near [di]
00000422  90                nop
00000423  97                xchg ax,di
00000424  0408              add al,0x8
00000426  681800            push word 0x18
00000429  0000              add [bx+si],al
0000042B  E9B0FF            jmp 0x3de
0000042E  FF                db 0xFF
0000042F  FF                db 0xFF
00000430  FF25              jmp near [di]
00000432  94                xchg ax,sp
00000433  97                xchg ax,di
00000434  0408              add al,0x8
00000436  682000            push word 0x20
00000439  0000              add [bx+si],al
0000043B  E9A0FF            jmp 0x3de
0000043E  FF                db 0xFF
0000043F  FF31              push word [bx+di]
00000441  ED                in ax,dx
00000442  5E                pop si
00000443  89E1              mov cx,sp
00000445  83E4F0            and sp,byte -0x10
00000448  50                push ax
00000449  54                push sp
0000044A  52                push dx
0000044B  689C85            push word 0x859c
0000044E  0408              add al,0x8
00000450  684885            push word 0x8548
00000453  0408              add al,0x8
00000455  51                push cx
00000456  56                push si
00000457  68E884            push word 0x84e8
0000045A  0408              add al,0x8
0000045C  E8AFFF            call 0x40e
0000045F  FF                db 0xFF
00000460  FFF4              push sp
00000462  90                nop
00000463  90                nop
00000464  55                push bp
00000465  89E5              mov bp,sp
00000467  53                push bx
00000468  E80000            call 0x46b
0000046B  0000              add [bx+si],al
0000046D  5B                pop bx
0000046E  81C30B13          add bx,0x130b
00000472  0000              add [bx+si],al
00000474  52                push dx
00000475  8B83FCFF          mov ax,[bp+di+0xfffc]
00000479  FF                db 0xFF
0000047A  FF85C074          inc word [di+0x74c0]
0000047E  02FF              add bh,bh
00000480  D0585B            rcr byte [bx+si+0x5b],1
00000483  C9                leave
00000484  C3                ret
00000485  90                nop
00000486  90                nop
00000487  90                nop
00000488  55                push bp
00000489  89E5              mov bp,sp
0000048B  83EC08            sub sp,byte +0x8
0000048E  803DA4            cmp byte [di],0xa4
00000491  97                xchg ax,di
00000492  0408              add al,0x8
00000494  00740F            add [si+0xf],dh
00000497  EB1F              jmp short 0x4b8
00000499  8D7600            lea si,[bp+0x0]
0000049C  83C004            add ax,byte +0x4
0000049F  A3A097            mov [0x97a0],ax
000004A2  0408              add al,0x8
000004A4  FFD2              call dx
000004A6  A1A097            mov ax,[0x97a0]
000004A9  0408              add al,0x8
000004AB  8B10              mov dx,[bx+si]
000004AD  85D2              test dx,dx
000004AF  75EB              jnz 0x49c
000004B1  C605A4            mov byte [di],0xa4
000004B4  97                xchg ax,di
000004B5  0408              add al,0x8
000004B7  01C9              add cx,cx
000004B9  C3                ret
000004BA  89F6              mov si,si
000004BC  55                push bp
000004BD  89E5              mov bp,sp
000004BF  83EC08            sub sp,byte +0x8
000004C2  A19096            mov ax,[0x9690]
000004C5  0408              add al,0x8
000004C7  85C0              test ax,ax
000004C9  7419              jz 0x4e4
000004CB  B80000            mov ax,0x0
000004CE  0000              add [bx+si],al
000004D0  85C0              test ax,ax
000004D2  7410              jz 0x4e4
000004D4  83EC0C            sub sp,byte +0xc
000004D7  689096            push word 0x9690
000004DA  0408              add al,0x8
000004DC  FFD0              call ax
000004DE  83C410            add sp,byte +0x10
000004E1  8D7600            lea si,[bp+0x0]
000004E4  C9                leave
000004E5  C3                ret
000004E6  90                nop
000004E7  90                nop
000004E8  55                push bp
000004E9  89E5              mov bp,sp
000004EB  83EC08            sub sp,byte +0x8
000004EE  83E4F0            and sp,byte -0x10
000004F1  83EC10            sub sp,byte +0x10
000004F4  90                nop
000004F5  90                nop
000004F6  90                nop
000004F7  90                nop
000004F8  90                nop
000004F9  90                nop
000004FA  90                nop
000004FB  90                nop
000004FC  90                nop
000004FD  90                nop
000004FE  90                nop
000004FF  90                nop
00000500  90                nop
00000501  90                nop
00000502  90                nop
00000503  90                nop
00000504  90                nop
00000505  90                nop
00000506  90                nop
00000507  90                nop
00000508  31C0              xor ax,ax
0000050A  C9                leave
0000050B  C3                ret
0000050C  55                push bp
0000050D  89E5              mov bp,sp
0000050F  C74508A897        mov word [di+0x8],0x97a8
00000514  0408              add al,0x8
00000516  C9                leave
00000517  E914FF            jmp 0x42e
0000051A  FF                db 0xFF
0000051B  FF5589            call near [di-0x77]
0000051E  E583              in ax,0x83
00000520  EC                in al,dx
00000521  1468              adc al,0x68
00000523  A897              test al,0x97
00000525  0408              add al,0x8
00000527  E8C4FE            call 0x3ee
0000052A  FF                db 0xFF
0000052B  FF83C40C          inc word [bp+di+0xcc4]
0000052F  689C97            push word 0x979c
00000532  0408              add al,0x8
00000534  6A00              push byte +0x0
00000536  680C85            push word 0x850c
00000539  0408              add al,0x8
0000053B  E8C0FE            call 0x3fe
0000053E  FF                db 0xFF
0000053F  FF83C410          inc word [bp+di+0x10c4]
00000543  C9                leave
00000544  C3                ret
00000545  90                nop
00000546  90                nop
00000547  90                nop
00000548  55                push bp
00000549  89E5              mov bp,sp
0000054B  57                push di
0000054C  56                push si
0000054D  53                push bx
0000054E  83EC0C            sub sp,byte +0xc
00000551  E80000            call 0x554
00000554  0000              add [bx+si],al
00000556  5B                pop bx
00000557  81C32212          add bx,0x1222
0000055B  0000              add [bx+si],al
0000055D  E866FE            call 0x3c6
00000560  FF                db 0xFF
00000561  FF8D8304          dec word [di+0x483]
00000565  FF                db 0xFF
00000566  FF                db 0xFF
00000567  FF8D9304          dec word [di+0x493]
0000056B  FF                db 0xFF
0000056C  FF                db 0xFF
0000056D  FF8945F0          dec word [bx+di+0xf045]
00000571  29D0              sub ax,dx
00000573  31F6              xor si,si
00000575  C1F802            sar ax,0x2
00000578  39C6              cmp si,ax
0000057A  7316              jnc 0x592
0000057C  89D7              mov di,dx
0000057E  89F6              mov si,si
00000580  FF14              call near [si]
00000582  B28B              mov dl,0x8b
00000584  4D                dec bp
00000585  F029F9            lock sub cx,di
00000588  46                inc si
00000589  C1F902            sar cx,0x2
0000058C  39CE              cmp si,cx
0000058E  89FA              mov dx,di
00000590  72EE              jc 0x580
00000592  83C40C            add sp,byte +0xc
00000595  5B                pop bx
00000596  5E                pop si
00000597  5F                pop di
00000598  C9                leave
00000599  C3                ret
0000059A  89F6              mov si,si
0000059C  55                push bp
0000059D  89E5              mov bp,sp
0000059F  57                push di
000005A0  56                push si
000005A1  53                push bx
000005A2  E80000            call 0x5a5
000005A5  0000              add [bx+si],al
000005A7  5B                pop bx
000005A8  81C3D111          add bx,0x11d1
000005AC  0000              add [bx+si],al
000005AE  8D8304FF          lea ax,[bp+di+0xff04]
000005B2  FF                db 0xFF
000005B3  FF8DBB04          dec word [di+0x4bb]
000005B7  FF                db 0xFF
000005B8  FF                db 0xFF
000005B9  FF29              jmp far [bx+di]
000005BB  F8                clc
000005BC  C1F802            sar ax,0x2
000005BF  83EC0C            sub sp,byte +0xc
000005C2  8D70FF            lea si,[bx+si-0x1]
000005C5  EB05              jmp short 0x5cc
000005C7  90                nop
000005C8  FF14              call near [si]
000005CA  B74E              mov bh,0x4e
000005CC  83FEFF            cmp si,byte -0x1
000005CF  75F7              jnz 0x5c8
000005D1  E82E00            call 0x602
000005D4  0000              add [bx+si],al
000005D6  83C40C            add sp,byte +0xc
000005D9  5B                pop bx
000005DA  5E                pop si
000005DB  5F                pop di
000005DC  C9                leave
000005DD  C3                ret
000005DE  90                nop
000005DF  90                nop
000005E0  55                push bp
000005E1  89E5              mov bp,sp
000005E3  53                push bx
000005E4  52                push dx
000005E5  BB8096            mov bx,0x9680
000005E8  0408              add al,0x8
000005EA  A18096            mov ax,[0x9680]
000005ED  0408              add al,0x8
000005EF  EB0A              jmp short 0x5fb
000005F1  8D7600            lea si,[bp+0x0]
000005F4  83EB04            sub bx,byte +0x4
000005F7  FFD0              call ax
000005F9  8B03              mov ax,[bp+di]
000005FB  83F8FF            cmp ax,byte -0x1
000005FE  75F4              jnz 0x5f4
00000600  58                pop ax
00000601  5B                pop bx
00000602  C9                leave
00000603  C3                ret
00000604  55                push bp
00000605  89E5              mov bp,sp
00000607  53                push bx
00000608  E80000            call 0x60b
0000060B  0000              add [bx+si],al
0000060D  5B                pop bx
0000060E  81C36B11          add bx,0x116b
00000612  0000              add [bx+si],al
00000614  50                push ax
00000615  E86EFE            call 0x486
00000618  FF                db 0xFF
00000619  FF595B            call far [bx+di+0x5b]
0000061C  C9                leave
0000061D  C3                ret
0000061E  0000              add [bx+si],al
00000620  0300              add ax,[bx+si]
00000622  0000              add [bx+si],al
00000624  0100              add [bx+si],ax
00000626  0200              add al,[bx+si]
00000628  011B              add [bp+di],bx
0000062A  033B              add di,[bp+di]
0000062C  1000              adc [bx+si],al
0000062E  0000              add [bx+si],al
00000630  0100              add [bx+si],ax
00000632  0000              add [bx+si],al
00000634  F4                hlt
00000635  FE                db 0xFE
00000636  FF                db 0xFF
00000637  FF30              push word [bx+si]
00000639  0000              add [bx+si],al
0000063B  0018              add [bx+si],bl
0000063D  0000              add [bx+si],al
0000063F  0000              add [bx+si],al
00000641  0000              add [bx+si],al
00000643  0001              add [bx+di],al
00000645  7A50              jpe 0x697
00000647  0001              add [bx+di],al
00000649  7C08              jl 0x653
0000064B  050020            add ax,0x2000
0000064E  8404              test [si],al
00000650  080C              or [si],cl
00000652  0404              add al,0x4
00000654  8801              mov [bx+di],al
00000656  0000              add [bx+si],al
00000658  1C00              sbb al,0x0
0000065A  0000              add [bx+si],al
0000065C  2000              and [bx+si],al
0000065E  0000              add [bx+si],al
00000660  1C85              sbb al,0x85
00000662  0408              add al,0x8
00000664  2900              sub [bx+si],ax
00000666  0000              add [bx+si],al
00000668  00410E            add [bx+di+0xe],al
0000066B  08850242          or [di+0x4202],al
0000066F  0D0548            or ax,0x4805
00000672  2E0454            cs add al,0x54
00000675  2E0C00            cs or al,0x0
00000678  0000              add [bx+si],al
0000067A  0000              add [bx+si],al
0000067C  FF                db 0xFF
0000067D  FF                db 0xFF
0000067E  FF                db 0xFF
0000067F  FF1C              call far [si]
00000681  8504              test [si],ax
00000683  0800              or [bx+si],al
00000685  0000              add [bx+si],al
00000687  00FF              add bh,bh
00000689  FF                db 0xFF
0000068A  FF                db 0xFF
0000068B  FF00              inc word [bx+si]
0000068D  0000              add [bx+si],al
0000068F  0000              add [bx+si],al
00000691  0000              add [bx+si],al
00000693  0001              add [bx+di],al
00000695  0000              add [bx+si],al
00000697  0001              add [bx+di],al
00000699  0000              add [bx+si],al
0000069B  0001              add [bx+di],al
0000069D  0000              add [bx+si],al
0000069F  007800            add [bx+si+0x0],bh
000006A2  0000              add [bx+si],al
000006A4  0100              add [bx+si],ax
000006A6  0000              add [bx+si],al
000006A8  82                db 0x82
000006A9  0000              add [bx+si],al
000006AB  0001              add [bx+di],al
000006AD  0000              add [bx+si],al
000006AF  00900000          add [bx+si+0x0],dl
000006B3  000C              add [si],cl
000006B5  0000              add [bx+si],al
000006B7  00C8              add al,cl
000006B9  830408            add word [si],byte +0x8
000006BC  0D0000            or ax,0x0
000006BF  0004              add [si],al
000006C1  8604              xchg al,[si]
000006C3  0804              or [si],al
000006C5  0000              add [bx+si],al
000006C7  006881            add [bx+si-0x7f],ch
000006CA  0408              add al,0x8
000006CC  050000            add ax,0x0
000006CF  0030              add [bx+si],dh
000006D1  82                db 0x82
000006D2  0408              add al,0x8
000006D4  06                push es
000006D5  0000              add [bx+si],al
000006D7  00A08104          add [bx+si+0x481],ah
000006DB  080A              or [bp+si],cl
000006DD  0000              add [bx+si],al
000006DF  00F5              add ch,dh
000006E1  0000              add [bx+si],al
000006E3  000B              add [bp+di],cl
000006E5  0000              add [bx+si],al
000006E7  0010              add [bx+si],dl
000006E9  0000              add [bx+si],al
000006EB  0015              add [di],dl
000006ED  0000              add [bx+si],al
000006EF  0000              add [bx+si],al
000006F1  0000              add [bx+si],al
000006F3  0003              add [bp+di],al
000006F5  0000              add [bx+si],al
000006F7  007897            add [bx+si-0x69],bh
000006FA  0408              add al,0x8
000006FC  0200              add al,[bx+si]
000006FE  0000              add [bx+si],al
00000700  2800              sub [bx+si],al
00000702  0000              add [bx+si],al
00000704  1400              adc al,0x0
00000706  0000              add [bx+si],al
00000708  1100              adc [bx+si],ax
0000070A  0000              add [bx+si],al
0000070C  17                pop ss
0000070D  0000              add [bx+si],al
0000070F  00A08304          add [bx+si+0x483],ah
00000713  0811              or [bx+di],dl
00000715  0000              add [bx+si],al
00000717  00988304          add [bx+si+0x483],bl
0000071B  0812              or [bp+si],dl
0000071D  0000              add [bx+si],al
0000071F  0008              add [bx+si],cl
00000721  0000              add [bx+si],al
00000723  0013              add [bp+di],dl
00000725  0000              add [bx+si],al
00000727  0008              add [bx+si],cl
00000729  0000              add [bx+si],al
0000072B  00FE              add dh,bh
0000072D  FF                db 0xFF
0000072E  FF6F38            jmp far [bx+0x38]
00000731  830408            add word [si],byte +0x8
00000734  FF                db 0xFF
00000735  FF                db 0xFF
00000736  FF6F02            jmp far [bx+0x2]
00000739  0000              add [bx+si],al
0000073B  00F0              add al,dh
0000073D  FF                db 0xFF
0000073E  FF6F26            jmp far [bx+0x26]
00000741  830408            add word [si],byte +0x8
00000744  0000              add [bx+si],al
00000746  0000              add [bx+si],al
00000748  0000              add [bx+si],al
0000074A  0000              add [bx+si],al
0000074C  0000              add [bx+si],al
0000074E  0000              add [bx+si],al
00000750  0000              add [bx+si],al
00000752  0000              add [bx+si],al
00000754  0000              add [bx+si],al
00000756  0000              add [bx+si],al
00000758  0000              add [bx+si],al
0000075A  0000              add [bx+si],al
0000075C  0000              add [bx+si],al
0000075E  0000              add [bx+si],al
00000760  0000              add [bx+si],al
00000762  0000              add [bx+si],al
00000764  0000              add [bx+si],al
00000766  0000              add [bx+si],al
00000768  0000              add [bx+si],al
0000076A  0000              add [bx+si],al
0000076C  0000              add [bx+si],al
0000076E  0000              add [bx+si],al
00000770  0000              add [bx+si],al
00000772  0000              add [bx+si],al
00000774  0000              add [bx+si],al
00000776  0000              add [bx+si],al
00000778  94                xchg ax,sp
00000779  96                xchg ax,si
0000077A  0408              add al,0x8
0000077C  0000              add [bx+si],al
0000077E  0000              add [bx+si],al
00000780  0000              add [bx+si],al
00000782  0000              add [bx+si],al
00000784  F683040806        test byte [bp+di+0x804],0x6
00000789  8404              test [si],al
0000078B  08168404          or [0x484],dl
0000078F  08268404          or [0x484],ah
00000793  08368404          or [0x484],dh
00000797  0800              or [bx+si],al
00000799  0000              add [bx+si],al
0000079B  0000              add [bx+si],al
0000079D  0000              add [bx+si],al
0000079F  008C9604          add [si+0x496],cl
000007A3  0800              or [bx+si],al
000007A5  47                inc di
000007A6  43                inc bx
000007A7  43                inc bx
000007A8  3A20              cmp ah,[bx+si]
000007AA  28474E            sub [bx+0x4e],al
000007AD  55                push bp
000007AE  2920              sub [bx+si],sp
000007B0  332E342E          xor bp,[0x2e34]
000007B4  362032            and [ss:bp+si],dh
000007B7  3030              xor [bx+si],dh
000007B9  363034            xor [ss:si],dh
000007BC  3034              xor [si],dh
000007BE  2028              and [bx+si],ch
000007C0  52                push dx
000007C1  6564204861        and [fs:bx+si+0x61],cl
000007C6  7420              jz 0x7e8
000007C8  332E342E          xor bp,[0x2e34]
000007CC  362D3329          ss sub ax,0x2933
000007D0  0000              add [bx+si],al
000007D2  47                inc di
000007D3  43                inc bx
000007D4  43                inc bx
000007D5  3A20              cmp ah,[bx+si]
000007D7  28474E            sub [bx+0x4e],al
000007DA  55                push bp
000007DB  2920              sub [bx+si],sp
000007DD  332E342E          xor bp,[0x2e34]
000007E1  362032            and [ss:bp+si],dh
000007E4  3030              xor [bx+si],dh
000007E6  363034            xor [ss:si],dh
000007E9  3034              xor [si],dh
000007EB  2028              and [bx+si],ch
000007ED  52                push dx
000007EE  6564204861        and [fs:bx+si+0x61],cl
000007F3  7420              jz 0x815
000007F5  332E342E          xor bp,[0x2e34]
000007F9  362D3329          ss sub ax,0x2933
000007FD  0000              add [bx+si],al
000007FF  47                inc di
00000800  43                inc bx
00000801  43                inc bx
00000802  3A20              cmp ah,[bx+si]
00000804  28474E            sub [bx+0x4e],al
00000807  55                push bp
00000808  2920              sub [bx+si],sp
0000080A  332E342E          xor bp,[0x2e34]
0000080E  362032            and [ss:bp+si],dh
00000811  3030              xor [bx+si],dh
00000813  363034            xor [ss:si],dh
00000816  3034              xor [si],dh
00000818  2028              and [bx+si],ch
0000081A  52                push dx
0000081B  6564204861        and [fs:bx+si+0x61],cl
00000820  7420              jz 0x842
00000822  332E342E          xor bp,[0x2e34]
00000826  362D3829          ss sub ax,0x2938
0000082A  0000              add [bx+si],al
0000082C  47                inc di
0000082D  43                inc bx
0000082E  43                inc bx
0000082F  3A20              cmp ah,[bx+si]
00000831  28474E            sub [bx+0x4e],al
00000834  55                push bp
00000835  2920              sub [bx+si],sp
00000837  332E342E          xor bp,[0x2e34]
0000083B  362032            and [ss:bp+si],dh
0000083E  3030              xor [bx+si],dh
00000840  363034            xor [ss:si],dh
00000843  3034              xor [si],dh
00000845  2028              and [bx+si],ch
00000847  52                push dx
00000848  6564204861        and [fs:bx+si+0x61],cl
0000084D  7420              jz 0x86f
0000084F  332E342E          xor bp,[0x2e34]
00000853  362D3829          ss sub ax,0x2938
00000857  0000              add [bx+si],al
00000859  47                inc di
0000085A  43                inc bx
0000085B  43                inc bx
0000085C  3A20              cmp ah,[bx+si]
0000085E  28474E            sub [bx+0x4e],al
00000861  55                push bp
00000862  2920              sub [bx+si],sp
00000864  332E342E          xor bp,[0x2e34]
00000868  362032            and [ss:bp+si],dh
0000086B  3030              xor [bx+si],dh
0000086D  363034            xor [ss:si],dh
00000870  3034              xor [si],dh
00000872  2028              and [bx+si],ch
00000874  52                push dx
00000875  6564204861        and [fs:bx+si+0x61],cl
0000087A  7420              jz 0x89c
0000087C  332E342E          xor bp,[0x2e34]
00000880  362D3829          ss sub ax,0x2938
00000884  0000              add [bx+si],al
00000886  47                inc di
00000887  43                inc bx
00000888  43                inc bx
00000889  3A20              cmp ah,[bx+si]
0000088B  28474E            sub [bx+0x4e],al
0000088E  55                push bp
0000088F  2920              sub [bx+si],sp
00000891  332E342E          xor bp,[0x2e34]
00000895  362032            and [ss:bp+si],dh
00000898  3030              xor [bx+si],dh
0000089A  363034            xor [ss:si],dh
0000089D  3034              xor [si],dh
0000089F  2028              and [bx+si],ch
000008A1  52                push dx
000008A2  6564204861        and [fs:bx+si+0x61],cl
000008A7  7420              jz 0x8c9
000008A9  332E342E          xor bp,[0x2e34]
000008AD  362D3329          ss sub ax,0x2933
000008B1  0000              add [bx+si],al
000008B3  2E7379            cs jnc 0x92f
000008B6  6D                insw
000008B7  7461              jz 0x91a
000008B9  6200              bound ax,[bx+si]
000008BB  2E7374            cs jnc 0x932
000008BE  7274              jc 0x934
000008C0  61                popa
000008C1  6200              bound ax,[bx+si]
000008C3  2E7368            cs jnc 0x92e
000008C6  7374              jnc 0x93c
000008C8  7274              jc 0x93e
000008CA  61                popa
000008CB  6200              bound ax,[bx+si]
000008CD  2E696E746572      imul bp,[cs:bp+0x74],word 0x7265
000008D3  7000              jo 0x8d5
000008D5  2E6E              cs outsb
000008D7  6F                outsw
000008D8  7465              jz 0x93f
000008DA  2E41              cs inc cx
000008DC  42                inc dx
000008DD  49                dec cx
000008DE  2D7461            sub ax,0x6174
000008E1  67002E            add [esi],ch
000008E4  686173            push word 0x7361
000008E7  68002E            push word 0x2e00
000008EA  64796E            fs jns 0x95b
000008ED  7379              jnc 0x968
000008EF  6D                insw
000008F0  002E6479          add [0x7964],ch
000008F4  6E                outsb
000008F5  7374              jnc 0x96b
000008F7  7200              jc 0x8f9
000008F9  2E676E            cs a32 outsb
000008FC  752E              jnz 0x92c
000008FE  7665              jna 0x965
00000900  7273              jc 0x975
00000902  696F6E002E        imul bp,[bx+0x6e],word 0x2e00
00000907  676E              a32 outsb
00000909  752E              jnz 0x939
0000090B  7665              jna 0x972
0000090D  7273              jc 0x982
0000090F  696F6E5F72        imul bp,[bx+0x6e],word 0x725f
00000914  002E7265          add [0x6572],ch
00000918  6C                insb
00000919  2E64796E          fs jns 0x98b
0000091D  002E7265          add [0x6572],ch
00000921  6C                insb
00000922  2E706C            cs jo 0x991
00000925  7400              jz 0x927
00000927  2E696E697400      imul bp,[cs:bp+0x69],word 0x74
0000092D  2E7465            cs jz 0x995
00000930  7874              js 0x9a6
00000932  002E6669          add [0x6966],ch
00000936  6E                outsb
00000937  69002E72          imul ax,[bx+si],word 0x722e
0000093B  6F                outsw
0000093C  6461              fs popa
0000093E  7461              jz 0x9a1
00000940  002E6568          add [0x6865],ch
00000944  5F                pop di
00000945  667261            o32 jc 0x9a9
00000948  6D                insw
00000949  655F              gs pop di
0000094B  686472            push word 0x7264
0000094E  002E6568          add [0x6865],ch
00000952  5F                pop di
00000953  667261            o32 jc 0x9b7
00000956  6D                insw
00000957  65002E6374        add [gs:0x7463],ch
0000095C  6F                outsw
0000095D  7273              jc 0x9d2
0000095F  002E6474          add [0x7464],ch
00000963  6F                outsw
00000964  7273              jc 0x9d9
00000966  002E6A63          add [0x636a],ch
0000096A  7200              jc 0x96c
0000096C  2E64796E          fs jns 0x9de
00000970  61                popa
00000971  6D                insw
00000972  6963002E67        imul sp,[bp+di+0x0],word 0x672e
00000977  6F                outsw
00000978  7400              jz 0x97a
0000097A  2E676F            cs a32 outsw
0000097D  742E              jz 0x9ad
0000097F  706C              jo 0x9ed
00000981  7400              jz 0x983
00000983  2E6461            fs popa
00000986  7461              jz 0x9e9
00000988  002E6273          add [0x7362],ch
0000098C  7300              jnc 0x98e
0000098E  2E636F6D          arpl [cs:bx+0x6d],bp
00000992  6D                insw
00000993  656E              gs outsb
00000995  7400              jz 0x997
00000997  0000              add [bx+si],al
00000999  0000              add [bx+si],al
0000099B  0000              add [bx+si],al
0000099D  0000              add [bx+si],al
0000099F  0000              add [bx+si],al
000009A1  0000              add [bx+si],al
000009A3  0000              add [bx+si],al
000009A5  0000              add [bx+si],al
000009A7  0000              add [bx+si],al
000009A9  0000              add [bx+si],al
000009AB  0000              add [bx+si],al
000009AD  0000              add [bx+si],al
000009AF  0000              add [bx+si],al
000009B1  0000              add [bx+si],al
000009B3  0000              add [bx+si],al
000009B5  0000              add [bx+si],al
000009B7  0000              add [bx+si],al
000009B9  0000              add [bx+si],al
000009BB  0000              add [bx+si],al
000009BD  0000              add [bx+si],al
000009BF  001B              add [bp+di],bl
000009C1  0000              add [bx+si],al
000009C3  0001              add [bx+di],al
000009C5  0000              add [bx+si],al
000009C7  0002              add [bp+si],al
000009C9  0000              add [bx+si],al
000009CB  0034              add [si],dh
000009CD  81040834          add word [si],0x3408
000009D1  0100              add [bx+si],ax
000009D3  0013              add [bp+di],dl
000009D5  0000              add [bx+si],al
000009D7  0000              add [bx+si],al
000009D9  0000              add [bx+si],al
000009DB  0000              add [bx+si],al
000009DD  0000              add [bx+si],al
000009DF  0001              add [bx+di],al
000009E1  0000              add [bx+si],al
000009E3  0000              add [bx+si],al
000009E5  0000              add [bx+si],al
000009E7  0023              add [bp+di],ah
000009E9  0000              add [bx+si],al
000009EB  0007              add [bx],al
000009ED  0000              add [bx+si],al
000009EF  0002              add [bp+si],al
000009F1  0000              add [bx+si],al
000009F3  004881            add [bx+si-0x7f],cl
000009F6  0408              add al,0x8
000009F8  48                dec ax
000009F9  0100              add [bx+si],ax
000009FB  0020              add [bx+si],ah
000009FD  0000              add [bx+si],al
000009FF  0000              add [bx+si],al
00000A01  0000              add [bx+si],al
00000A03  0000              add [bx+si],al
00000A05  0000              add [bx+si],al
00000A07  0004              add [si],al
00000A09  0000              add [bx+si],al
00000A0B  0000              add [bx+si],al
00000A0D  0000              add [bx+si],al
00000A0F  0031              add [bx+di],dh
00000A11  0000              add [bx+si],al
00000A13  0005              add [di],al
00000A15  0000              add [bx+si],al
00000A17  0002              add [bp+si],al
00000A19  0000              add [bx+si],al
00000A1B  006881            add [bx+si-0x7f],ch
00000A1E  0408              add al,0x8
00000A20  680100            push word 0x1
00000A23  0038              add [bx+si],bh
00000A25  0000              add [bx+si],al
00000A27  0004              add [si],al
00000A29  0000              add [bx+si],al
00000A2B  0000              add [bx+si],al
00000A2D  0000              add [bx+si],al
00000A2F  0004              add [si],al
00000A31  0000              add [bx+si],al
00000A33  0004              add [si],al
00000A35  0000              add [bx+si],al
00000A37  0037              add [bx],dh
00000A39  0000              add [bx+si],al
00000A3B  000B              add [bp+di],cl
00000A3D  0000              add [bx+si],al
00000A3F  0002              add [bp+si],al
00000A41  0000              add [bx+si],al
00000A43  00A08104          add [bx+si+0x481],ah
00000A47  08A00100          or [bx+si+0x1],ah
00000A4B  00900000          add [bx+si+0x0],dl
00000A4F  0005              add [di],al
00000A51  0000              add [bx+si],al
00000A53  0001              add [bx+di],al
00000A55  0000              add [bx+si],al
00000A57  0004              add [si],al
00000A59  0000              add [bx+si],al
00000A5B  0010              add [bx+si],dl
00000A5D  0000              add [bx+si],al
00000A5F  003F              add [bx],bh
00000A61  0000              add [bx+si],al
00000A63  0003              add [bp+di],al
00000A65  0000              add [bx+si],al
00000A67  0002              add [bp+si],al
00000A69  0000              add [bx+si],al
00000A6B  0030              add [bx+si],dh
00000A6D  82                db 0x82
00000A6E  0408              add al,0x8
00000A70  3002              xor [bp+si],al
00000A72  0000              add [bx+si],al
00000A74  F5                cmc
00000A75  0000              add [bx+si],al
00000A77  0000              add [bx+si],al
00000A79  0000              add [bx+si],al
00000A7B  0000              add [bx+si],al
00000A7D  0000              add [bx+si],al
00000A7F  0001              add [bx+di],al
00000A81  0000              add [bx+si],al
00000A83  0000              add [bx+si],al
00000A85  0000              add [bx+si],al
00000A87  004700            add [bx+0x0],al
00000A8A  0000              add [bx+si],al
00000A8C  FF                db 0xFF
00000A8D  FF                db 0xFF
00000A8E  FF6F02            jmp far [bx+0x2]
00000A91  0000              add [bx+si],al
00000A93  00268304          add [0x483],ah
00000A97  08260300          or [0x3],ah
00000A9B  0012              add [bp+si],dl
00000A9D  0000              add [bx+si],al
00000A9F  0004              add [si],al
00000AA1  0000              add [bx+si],al
00000AA3  0000              add [bx+si],al
00000AA5  0000              add [bx+si],al
00000AA7  0002              add [bp+si],al
00000AA9  0000              add [bx+si],al
00000AAB  0002              add [bp+si],al
00000AAD  0000              add [bx+si],al
00000AAF  005400            add [si+0x0],dl
00000AB2  0000              add [bx+si],al
00000AB4  FE                db 0xFE
00000AB5  FF                db 0xFF
00000AB6  FF6F02            jmp far [bx+0x2]
00000AB9  0000              add [bx+si],al
00000ABB  0038              add [bx+si],bh
00000ABD  830408            add word [si],byte +0x8
00000AC0  3803              cmp [bp+di],al
00000AC2  0000              add [bx+si],al
00000AC4  60                pusha
00000AC5  0000              add [bx+si],al
00000AC7  0005              add [di],al
00000AC9  0000              add [bx+si],al
00000ACB  0002              add [bp+si],al
00000ACD  0000              add [bx+si],al
00000ACF  0004              add [si],al
00000AD1  0000              add [bx+si],al
00000AD3  0000              add [bx+si],al
00000AD5  0000              add [bx+si],al
00000AD7  006300            add [bp+di+0x0],ah
00000ADA  0000              add [bx+si],al
00000ADC  0900              or [bx+si],ax
00000ADE  0000              add [bx+si],al
00000AE0  0200              add al,[bx+si]
00000AE2  0000              add [bx+si],al
00000AE4  98                cbw
00000AE5  830408            add word [si],byte +0x8
00000AE8  98                cbw
00000AE9  0300              add ax,[bx+si]
00000AEB  0008              add [bx+si],cl
00000AED  0000              add [bx+si],al
00000AEF  0004              add [si],al
00000AF1  0000              add [bx+si],al
00000AF3  0000              add [bx+si],al
00000AF5  0000              add [bx+si],al
00000AF7  0004              add [si],al
00000AF9  0000              add [bx+si],al
00000AFB  0008              add [bx+si],cl
00000AFD  0000              add [bx+si],al
00000AFF  006C00            add [si+0x0],ch
00000B02  0000              add [bx+si],al
00000B04  0900              or [bx+si],ax
00000B06  0000              add [bx+si],al
00000B08  0200              add al,[bx+si]
00000B0A  0000              add [bx+si],al
00000B0C  A08304            mov al,[0x483]
00000B0F  08A00300          or [bx+si+0x3],ah
00000B13  0028              add [bx+si],ch
00000B15  0000              add [bx+si],al
00000B17  0004              add [si],al
00000B19  0000              add [bx+si],al
00000B1B  000B              add [bp+di],cl
00000B1D  0000              add [bx+si],al
00000B1F  0004              add [si],al
00000B21  0000              add [bx+si],al
00000B23  0008              add [bx+si],cl
00000B25  0000              add [bx+si],al
00000B27  007500            add [di+0x0],dh
00000B2A  0000              add [bx+si],al
00000B2C  0100              add [bx+si],ax
00000B2E  0000              add [bx+si],al
00000B30  06                push es
00000B31  0000              add [bx+si],al
00000B33  00C8              add al,cl
00000B35  830408            add word [si],byte +0x8
00000B38  C8030000          enter 0x3,0x0
00000B3C  17                pop ss
00000B3D  0000              add [bx+si],al
00000B3F  0000              add [bx+si],al
00000B41  0000              add [bx+si],al
00000B43  0000              add [bx+si],al
00000B45  0000              add [bx+si],al
00000B47  0004              add [si],al
00000B49  0000              add [bx+si],al
00000B4B  0000              add [bx+si],al
00000B4D  0000              add [bx+si],al
00000B4F  007000            add [bx+si+0x0],dh
00000B52  0000              add [bx+si],al
00000B54  0100              add [bx+si],ax
00000B56  0000              add [bx+si],al
00000B58  06                push es
00000B59  0000              add [bx+si],al
00000B5B  00E0              add al,ah
00000B5D  830408            add word [si],byte +0x8
00000B60  E003              loopne 0xb65
00000B62  0000              add [bx+si],al
00000B64  60                pusha
00000B65  0000              add [bx+si],al
00000B67  0000              add [bx+si],al
00000B69  0000              add [bx+si],al
00000B6B  0000              add [bx+si],al
00000B6D  0000              add [bx+si],al
00000B6F  0004              add [si],al
00000B71  0000              add [bx+si],al
00000B73  0004              add [si],al
00000B75  0000              add [bx+si],al
00000B77  007B00            add [bp+di+0x0],bh
00000B7A  0000              add [bx+si],al
00000B7C  0100              add [bx+si],ax
00000B7E  0000              add [bx+si],al
00000B80  06                push es
00000B81  0000              add [bx+si],al
00000B83  004084            add [bx+si-0x7c],al
00000B86  0408              add al,0x8
00000B88  40                inc ax
00000B89  0400              add al,0x0
00000B8B  00C4              add ah,al
00000B8D  0100              add [bx+si],ax
00000B8F  0000              add [bx+si],al
00000B91  0000              add [bx+si],al
00000B93  0000              add [bx+si],al
00000B95  0000              add [bx+si],al
00000B97  0004              add [si],al
00000B99  0000              add [bx+si],al
00000B9B  0000              add [bx+si],al
00000B9D  0000              add [bx+si],al
00000B9F  00810000          add [bx+di+0x0],al
00000BA3  0001              add [bx+di],al
00000BA5  0000              add [bx+si],al
00000BA7  00060000          add [0x0],al
00000BAB  0004              add [si],al
00000BAD  8604              xchg al,[si]
00000BAF  0804              or [si],al
00000BB1  06                push es
00000BB2  0000              add [bx+si],al
00000BB4  1A00              sbb al,[bx+si]
00000BB6  0000              add [bx+si],al
00000BB8  0000              add [bx+si],al
00000BBA  0000              add [bx+si],al
00000BBC  0000              add [bx+si],al
00000BBE  0000              add [bx+si],al
00000BC0  0400              add al,0x0
00000BC2  0000              add [bx+si],al
00000BC4  0000              add [bx+si],al
00000BC6  0000              add [bx+si],al
00000BC8  8700              xchg ax,[bx+si]
00000BCA  0000              add [bx+si],al
00000BCC  0100              add [bx+si],ax
00000BCE  0000              add [bx+si],al
00000BD0  0200              add al,[bx+si]
00000BD2  0000              add [bx+si],al
00000BD4  20860408          and [bp+0x804],al
00000BD8  20060000          and [0x0],al
00000BDC  0800              or [bx+si],al
00000BDE  0000              add [bx+si],al
00000BE0  0000              add [bx+si],al
00000BE2  0000              add [bx+si],al
00000BE4  0000              add [bx+si],al
00000BE6  0000              add [bx+si],al
00000BE8  0400              add al,0x0
00000BEA  0000              add [bx+si],al
00000BEC  0000              add [bx+si],al
00000BEE  0000              add [bx+si],al
00000BF0  8F00              pop word [bx+si]
00000BF2  0000              add [bx+si],al
00000BF4  0100              add [bx+si],ax
00000BF6  0000              add [bx+si],al
00000BF8  0200              add al,[bx+si]
00000BFA  0000              add [bx+si],al
00000BFC  28860408          sub [bp+0x804],al
00000C00  28060000          sub [0x0],al
00000C04  1400              adc al,0x0
00000C06  0000              add [bx+si],al
00000C08  0000              add [bx+si],al
00000C0A  0000              add [bx+si],al
00000C0C  0000              add [bx+si],al
00000C0E  0000              add [bx+si],al
00000C10  0400              add al,0x0
00000C12  0000              add [bx+si],al
00000C14  0000              add [bx+si],al
00000C16  0000              add [bx+si],al
00000C18  9D                popf
00000C19  0000              add [bx+si],al
00000C1B  0001              add [bx+di],al
00000C1D  0000              add [bx+si],al
00000C1F  0002              add [bp+si],al
00000C21  0000              add [bx+si],al
00000C23  003C              add [si],bh
00000C25  8604              xchg al,[si]
00000C27  083C              or [si],bh
00000C29  06                push es
00000C2A  0000              add [bx+si],al
00000C2C  40                inc ax
00000C2D  0000              add [bx+si],al
00000C2F  0000              add [bx+si],al
00000C31  0000              add [bx+si],al
00000C33  0000              add [bx+si],al
00000C35  0000              add [bx+si],al
00000C37  0004              add [si],al
00000C39  0000              add [bx+si],al
00000C3B  0000              add [bx+si],al
00000C3D  0000              add [bx+si],al
00000C3F  00A70000          add [bx+0x0],ah
00000C43  0001              add [bx+di],al
00000C45  0000              add [bx+si],al
00000C47  0003              add [bp+di],al
00000C49  0000              add [bx+si],al
00000C4B  007C96            add [si-0x6a],bh
00000C4E  0408              add al,0x8
00000C50  7C06              jl 0xc58
00000C52  0000              add [bx+si],al
00000C54  0C00              or al,0x0
00000C56  0000              add [bx+si],al
00000C58  0000              add [bx+si],al
00000C5A  0000              add [bx+si],al
00000C5C  0000              add [bx+si],al
00000C5E  0000              add [bx+si],al
00000C60  0400              add al,0x0
00000C62  0000              add [bx+si],al
00000C64  0000              add [bx+si],al
00000C66  0000              add [bx+si],al
00000C68  AE                scasb
00000C69  0000              add [bx+si],al
00000C6B  0001              add [bx+di],al
00000C6D  0000              add [bx+si],al
00000C6F  0003              add [bp+di],al
00000C71  0000              add [bx+si],al
00000C73  00889604          add [bx+si+0x496],cl
00000C77  08880600          or [bx+si+0x6],cl
00000C7B  0008              add [bx+si],cl
00000C7D  0000              add [bx+si],al
00000C7F  0000              add [bx+si],al
00000C81  0000              add [bx+si],al
00000C83  0000              add [bx+si],al
00000C85  0000              add [bx+si],al
00000C87  0004              add [si],al
00000C89  0000              add [bx+si],al
00000C8B  0000              add [bx+si],al
00000C8D  0000              add [bx+si],al
00000C8F  00B50000          add [di+0x0],dh
00000C93  0001              add [bx+di],al
00000C95  0000              add [bx+si],al
00000C97  0003              add [bp+di],al
00000C99  0000              add [bx+si],al
00000C9B  00909604          add [bx+si+0x496],dl
00000C9F  08900600          or [bx+si+0x6],dl
00000CA3  0004              add [si],al
00000CA5  0000              add [bx+si],al
00000CA7  0000              add [bx+si],al
00000CA9  0000              add [bx+si],al
00000CAB  0000              add [bx+si],al
00000CAD  0000              add [bx+si],al
00000CAF  0004              add [si],al
00000CB1  0000              add [bx+si],al
00000CB3  0000              add [bx+si],al
00000CB5  0000              add [bx+si],al
00000CB7  00BA0000          add [bp+si+0x0],bh
00000CBB  00060000          add [0x0],al
00000CBF  0003              add [bp+di],al
00000CC1  0000              add [bx+si],al
00000CC3  00949604          add [si+0x496],dl
00000CC7  08940600          or [si+0x6],dl
00000CCB  00E0              add al,ah
00000CCD  0000              add [bx+si],al
00000CCF  0005              add [di],al
00000CD1  0000              add [bx+si],al
00000CD3  0000              add [bx+si],al
00000CD5  0000              add [bx+si],al
00000CD7  0004              add [si],al
00000CD9  0000              add [bx+si],al
00000CDB  0008              add [bx+si],cl
00000CDD  0000              add [bx+si],al
00000CDF  00C3              add bl,al
00000CE1  0000              add [bx+si],al
00000CE3  0001              add [bx+di],al
00000CE5  0000              add [bx+si],al
00000CE7  0003              add [bp+di],al
00000CE9  0000              add [bx+si],al
00000CEB  007497            add [si-0x69],dh
00000CEE  0408              add al,0x8
00000CF0  7407              jz 0xcf9
00000CF2  0000              add [bx+si],al
00000CF4  0400              add al,0x0
00000CF6  0000              add [bx+si],al
00000CF8  0000              add [bx+si],al
00000CFA  0000              add [bx+si],al
00000CFC  0000              add [bx+si],al
00000CFE  0000              add [bx+si],al
00000D00  0400              add al,0x0
00000D02  0000              add [bx+si],al
00000D04  0400              add al,0x0
00000D06  0000              add [bx+si],al
00000D08  C8000000          enter 0x0,0x0
00000D0C  0100              add [bx+si],ax
00000D0E  0000              add [bx+si],al
00000D10  0300              add ax,[bx+si]
00000D12  0000              add [bx+si],al
00000D14  7897              js 0xcad
00000D16  0408              add al,0x8
00000D18  7807              js 0xd21
00000D1A  0000              add [bx+si],al
00000D1C  2000              and [bx+si],al
00000D1E  0000              add [bx+si],al
00000D20  0000              add [bx+si],al
00000D22  0000              add [bx+si],al
00000D24  0000              add [bx+si],al
00000D26  0000              add [bx+si],al
00000D28  0400              add al,0x0
00000D2A  0000              add [bx+si],al
00000D2C  0400              add al,0x0
00000D2E  0000              add [bx+si],al
00000D30  D100              rol word [bx+si],1
00000D32  0000              add [bx+si],al
00000D34  0100              add [bx+si],ax
00000D36  0000              add [bx+si],al
00000D38  0300              add ax,[bx+si]
00000D3A  0000              add [bx+si],al
00000D3C  98                cbw
00000D3D  97                xchg ax,di
00000D3E  0408              add al,0x8
00000D40  98                cbw
00000D41  07                pop es
00000D42  0000              add [bx+si],al
00000D44  0C00              or al,0x0
00000D46  0000              add [bx+si],al
00000D48  0000              add [bx+si],al
00000D4A  0000              add [bx+si],al
00000D4C  0000              add [bx+si],al
00000D4E  0000              add [bx+si],al
00000D50  0400              add al,0x0
00000D52  0000              add [bx+si],al
00000D54  0000              add [bx+si],al
00000D56  0000              add [bx+si],al
00000D58  D7                xlatb
00000D59  0000              add [bx+si],al
00000D5B  0008              add [bx+si],cl
00000D5D  0000              add [bx+si],al
00000D5F  0003              add [bp+di],al
00000D61  0000              add [bx+si],al
00000D63  00A49704          add [si+0x497],ah
00000D67  08A40700          or [si+0x7],ah
00000D6B  0008              add [bx+si],cl
00000D6D  0000              add [bx+si],al
00000D6F  0000              add [bx+si],al
00000D71  0000              add [bx+si],al
00000D73  0000              add [bx+si],al
00000D75  0000              add [bx+si],al
00000D77  0004              add [si],al
00000D79  0000              add [bx+si],al
00000D7B  0000              add [bx+si],al
00000D7D  0000              add [bx+si],al
00000D7F  00DC              add ah,bl
00000D81  0000              add [bx+si],al
00000D83  0001              add [bx+di],al
00000D85  0000              add [bx+si],al
00000D87  0000              add [bx+si],al
00000D89  0000              add [bx+si],al
00000D8B  0000              add [bx+si],al
00000D8D  0000              add [bx+si],al
00000D8F  00A40700          add [si+0x7],ah
00000D93  000E0100          add [0x1],cl
00000D97  0000              add [bx+si],al
00000D99  0000              add [bx+si],al
00000D9B  0000              add [bx+si],al
00000D9D  0000              add [bx+si],al
00000D9F  0001              add [bx+di],al
00000DA1  0000              add [bx+si],al
00000DA3  0000              add [bx+si],al
00000DA5  0000              add [bx+si],al
00000DA7  0011              add [bx+di],dl
00000DA9  0000              add [bx+si],al
00000DAB  0003              add [bp+di],al
00000DAD  0000              add [bx+si],al
00000DAF  0000              add [bx+si],al
00000DB1  0000              add [bx+si],al
00000DB3  0000              add [bx+si],al
00000DB5  0000              add [bx+si],al
00000DB7  00B20800          add [bp+si+0x8],dh
00000DBB  00E5              add ch,ah
00000DBD  0000              add [bx+si],al
00000DBF  0000              add [bx+si],al
00000DC1  0000              add [bx+si],al
00000DC3  0000              add [bx+si],al
00000DC5  0000              add [bx+si],al
00000DC7  0001              add [bx+di],al
00000DC9  0000              add [bx+si],al
00000DCB  0000              add [bx+si],al
00000DCD  0000              add [bx+si],al
00000DCF  0001              add [bx+di],al
00000DD1  0000              add [bx+si],al
00000DD3  0002              add [bp+si],al
00000DD5  0000              add [bx+si],al
00000DD7  0000              add [bx+si],al
00000DD9  0000              add [bx+si],al
00000DDB  0000              add [bx+si],al
00000DDD  0000              add [bx+si],al
00000DDF  0020              add [bx+si],ah
00000DE1  0E                push cs
00000DE2  0000              add [bx+si],al
00000DE4  D004              rol byte [si],1
00000DE6  0000              add [bx+si],al
00000DE8  1C00              sbb al,0x0
00000DEA  0000              add [bx+si],al
00000DEC  3000              xor [bx+si],al
00000DEE  0000              add [bx+si],al
00000DF0  0400              add al,0x0
00000DF2  0000              add [bx+si],al
00000DF4  1000              adc [bx+si],al
00000DF6  0000              add [bx+si],al
00000DF8  0900              or [bx+si],ax
00000DFA  0000              add [bx+si],al
00000DFC  0300              add ax,[bx+si]
00000DFE  0000              add [bx+si],al
00000E00  0000              add [bx+si],al
00000E02  0000              add [bx+si],al
00000E04  0000              add [bx+si],al
00000E06  0000              add [bx+si],al
00000E08  F01200            lock adc al,[bx+si]
00000E0B  00D0              add al,dl
00000E0D  0200              add al,[bx+si]
00000E0F  0000              add [bx+si],al
00000E11  0000              add [bx+si],al
00000E13  0000              add [bx+si],al
00000E15  0000              add [bx+si],al
00000E17  0001              add [bx+di],al
00000E19  0000              add [bx+si],al
00000E1B  0000              add [bx+si],al
00000E1D  0000              add [bx+si],al
00000E1F  0000              add [bx+si],al
00000E21  0000              add [bx+si],al
00000E23  0000              add [bx+si],al
00000E25  0000              add [bx+si],al
00000E27  0000              add [bx+si],al
00000E29  0000              add [bx+si],al
00000E2B  0000              add [bx+si],al
00000E2D  0000              add [bx+si],al
00000E2F  0000              add [bx+si],al
00000E31  0000              add [bx+si],al
00000E33  0034              add [si],dh
00000E35  81040800          add word [si],0x8
00000E39  0000              add [bx+si],al
00000E3B  0003              add [bp+di],al
00000E3D  0001              add [bx+di],al
00000E3F  0000              add [bx+si],al
00000E41  0000              add [bx+si],al
00000E43  004881            add [bx+si-0x7f],cl
00000E46  0408              add al,0x8
00000E48  0000              add [bx+si],al
00000E4A  0000              add [bx+si],al
00000E4C  0300              add ax,[bx+si]
00000E4E  0200              add al,[bx+si]
00000E50  0000              add [bx+si],al
00000E52  0000              add [bx+si],al
00000E54  688104            push word 0x481
00000E57  0800              or [bx+si],al
00000E59  0000              add [bx+si],al
00000E5B  0003              add [bp+di],al
00000E5D  0003              add [bp+di],al
00000E5F  0000              add [bx+si],al
00000E61  0000              add [bx+si],al
00000E63  00A08104          add [bx+si+0x481],ah
00000E67  0800              or [bx+si],al
00000E69  0000              add [bx+si],al
00000E6B  0003              add [bp+di],al
00000E6D  0004              add [si],al
00000E6F  0000              add [bx+si],al
00000E71  0000              add [bx+si],al
00000E73  0030              add [bx+si],dh
00000E75  82                db 0x82
00000E76  0408              add al,0x8
00000E78  0000              add [bx+si],al
00000E7A  0000              add [bx+si],al
00000E7C  0300              add ax,[bx+si]
00000E7E  050000            add ax,0x0
00000E81  0000              add [bx+si],al
00000E83  00268304          add [0x483],ah
00000E87  0800              or [bx+si],al
00000E89  0000              add [bx+si],al
00000E8B  0003              add [bp+di],al
00000E8D  00060000          add [0x0],al
00000E91  0000              add [bx+si],al
00000E93  0038              add [bx+si],bh
00000E95  830408            add word [si],byte +0x8
00000E98  0000              add [bx+si],al
00000E9A  0000              add [bx+si],al
00000E9C  0300              add ax,[bx+si]
00000E9E  07                pop es
00000E9F  0000              add [bx+si],al
00000EA1  0000              add [bx+si],al
00000EA3  00988304          add [bx+si+0x483],bl
00000EA7  0800              or [bx+si],al
00000EA9  0000              add [bx+si],al
00000EAB  0003              add [bp+di],al
00000EAD  0008              add [bx+si],cl
00000EAF  0000              add [bx+si],al
00000EB1  0000              add [bx+si],al
00000EB3  00A08304          add [bx+si+0x483],ah
00000EB7  0800              or [bx+si],al
00000EB9  0000              add [bx+si],al
00000EBB  0003              add [bp+di],al
00000EBD  0009              add [bx+di],cl
00000EBF  0000              add [bx+si],al
00000EC1  0000              add [bx+si],al
00000EC3  00C8              add al,cl
00000EC5  830408            add word [si],byte +0x8
00000EC8  0000              add [bx+si],al
00000ECA  0000              add [bx+si],al
00000ECC  0300              add ax,[bx+si]
00000ECE  0A00              or al,[bx+si]
00000ED0  0000              add [bx+si],al
00000ED2  0000              add [bx+si],al
00000ED4  E083              loopne 0xe59
00000ED6  0408              add al,0x8
00000ED8  0000              add [bx+si],al
00000EDA  0000              add [bx+si],al
00000EDC  0300              add ax,[bx+si]
00000EDE  0B00              or ax,[bx+si]
00000EE0  0000              add [bx+si],al
00000EE2  0000              add [bx+si],al
00000EE4  40                inc ax
00000EE5  8404              test [si],al
00000EE7  0800              or [bx+si],al
00000EE9  0000              add [bx+si],al
00000EEB  0003              add [bp+di],al
00000EED  000C              add [si],cl
00000EEF  0000              add [bx+si],al
00000EF1  0000              add [bx+si],al
00000EF3  0004              add [si],al
00000EF5  8604              xchg al,[si]
00000EF7  0800              or [bx+si],al
00000EF9  0000              add [bx+si],al
00000EFB  0003              add [bp+di],al
00000EFD  000D              add [di],cl
00000EFF  0000              add [bx+si],al
00000F01  0000              add [bx+si],al
00000F03  0020              add [bx+si],ah
00000F05  8604              xchg al,[si]
00000F07  0800              or [bx+si],al
00000F09  0000              add [bx+si],al
00000F0B  0003              add [bp+di],al
00000F0D  000E0000          add [0x0],cl
00000F11  0000              add [bx+si],al
00000F13  0028              add [bx+si],ch
00000F15  8604              xchg al,[si]
00000F17  0800              or [bx+si],al
00000F19  0000              add [bx+si],al
00000F1B  0003              add [bp+di],al
00000F1D  000F              add [bx],cl
00000F1F  0000              add [bx+si],al
00000F21  0000              add [bx+si],al
00000F23  003C              add [si],bh
00000F25  8604              xchg al,[si]
00000F27  0800              or [bx+si],al
00000F29  0000              add [bx+si],al
00000F2B  0003              add [bp+di],al
00000F2D  0010              add [bx+si],dl
00000F2F  0000              add [bx+si],al
00000F31  0000              add [bx+si],al
00000F33  007C96            add [si-0x6a],bh
00000F36  0408              add al,0x8
00000F38  0000              add [bx+si],al
00000F3A  0000              add [bx+si],al
00000F3C  0300              add ax,[bx+si]
00000F3E  1100              adc [bx+si],ax
00000F40  0000              add [bx+si],al
00000F42  0000              add [bx+si],al
00000F44  88960408          mov [bp+0x804],dl
00000F48  0000              add [bx+si],al
00000F4A  0000              add [bx+si],al
00000F4C  0300              add ax,[bx+si]
00000F4E  1200              adc al,[bx+si]
00000F50  0000              add [bx+si],al
00000F52  0000              add [bx+si],al
00000F54  90                nop
00000F55  96                xchg ax,si
00000F56  0408              add al,0x8
00000F58  0000              add [bx+si],al
00000F5A  0000              add [bx+si],al
00000F5C  0300              add ax,[bx+si]
00000F5E  1300              adc ax,[bx+si]
00000F60  0000              add [bx+si],al
00000F62  0000              add [bx+si],al
00000F64  94                xchg ax,sp
00000F65  96                xchg ax,si
00000F66  0408              add al,0x8
00000F68  0000              add [bx+si],al
00000F6A  0000              add [bx+si],al
00000F6C  0300              add ax,[bx+si]
00000F6E  1400              adc al,0x0
00000F70  0000              add [bx+si],al
00000F72  0000              add [bx+si],al
00000F74  7497              jz 0xf0d
00000F76  0408              add al,0x8
00000F78  0000              add [bx+si],al
00000F7A  0000              add [bx+si],al
00000F7C  0300              add ax,[bx+si]
00000F7E  150000            adc ax,0x0
00000F81  0000              add [bx+si],al
00000F83  007897            add [bx+si-0x69],bh
00000F86  0408              add al,0x8
00000F88  0000              add [bx+si],al
00000F8A  0000              add [bx+si],al
00000F8C  0300              add ax,[bx+si]
00000F8E  16                push ss
00000F8F  0000              add [bx+si],al
00000F91  0000              add [bx+si],al
00000F93  00989704          add [bx+si+0x497],bl
00000F97  0800              or [bx+si],al
00000F99  0000              add [bx+si],al
00000F9B  0003              add [bp+di],al
00000F9D  0017              add [bx],dl
00000F9F  0000              add [bx+si],al
00000FA1  0000              add [bx+si],al
00000FA3  00A49704          add [si+0x497],ah
00000FA7  0800              or [bx+si],al
00000FA9  0000              add [bx+si],al
00000FAB  0003              add [bp+di],al
00000FAD  0018              add [bx+si],bl
00000FAF  0000              add [bx+si],al
00000FB1  0000              add [bx+si],al
00000FB3  0000              add [bx+si],al
00000FB5  0000              add [bx+si],al
00000FB7  0000              add [bx+si],al
00000FB9  0000              add [bx+si],al
00000FBB  0003              add [bp+di],al
00000FBD  0019              add [bx+di],bl
00000FBF  0000              add [bx+si],al
00000FC1  0000              add [bx+si],al
00000FC3  0000              add [bx+si],al
00000FC5  0000              add [bx+si],al
00000FC7  0000              add [bx+si],al
00000FC9  0000              add [bx+si],al
00000FCB  0003              add [bp+di],al
00000FCD  001A              add [bp+si],bl
00000FCF  0000              add [bx+si],al
00000FD1  0000              add [bx+si],al
00000FD3  0000              add [bx+si],al
00000FD5  0000              add [bx+si],al
00000FD7  0000              add [bx+si],al
00000FD9  0000              add [bx+si],al
00000FDB  0003              add [bp+di],al
00000FDD  001B              add [bp+di],bl
00000FDF  0000              add [bx+si],al
00000FE1  0000              add [bx+si],al
00000FE3  0000              add [bx+si],al
00000FE5  0000              add [bx+si],al
00000FE7  0000              add [bx+si],al
00000FE9  0000              add [bx+si],al
00000FEB  0003              add [bp+di],al
00000FED  001C              add [si],bl
00000FEF  0001              add [bx+di],al
00000FF1  0000              add [bx+si],al
00000FF3  006484            add [si-0x7c],ah
00000FF6  0408              add al,0x8
00000FF8  0000              add [bx+si],al
00000FFA  0000              add [bx+si],al
00000FFC  0200              add al,[bx+si]
00000FFE  0C00              or al,0x0
00001000  1100              adc [bx+si],ax
00001002  0000              add [bx+si],al
00001004  0000              add [bx+si],al
00001006  0000              add [bx+si],al
00001008  0000              add [bx+si],al
0000100A  0000              add [bx+si],al
0000100C  0400              add al,0x0
0000100E  F1                int1
0000100F  FF1C              call far [si]
00001011  0000              add [bx+si],al
00001013  007C96            add [si-0x6a],bh
00001016  0408              add al,0x8
00001018  0000              add [bx+si],al
0000101A  0000              add [bx+si],al
0000101C  0100              add [bx+si],ax
0000101E  1100              adc [bx+si],ax
00001020  2A00              sub al,[bx+si]
00001022  0000              add [bx+si],al
00001024  88960408          mov [bp+0x804],dl
00001028  0000              add [bx+si],al
0000102A  0000              add [bx+si],al
0000102C  0100              add [bx+si],ax
0000102E  1200              adc al,[bx+si]
00001030  3800              cmp [bx+si],al
00001032  0000              add [bx+si],al
00001034  90                nop
00001035  96                xchg ax,si
00001036  0408              add al,0x8
00001038  0000              add [bx+si],al
0000103A  0000              add [bx+si],al
0000103C  0100              add [bx+si],ax
0000103E  1300              adc ax,[bx+si]
00001040  45                inc bp
00001041  0000              add [bx+si],al
00001043  00A09704          add [bx+si+0x497],ah
00001047  0800              or [bx+si],al
00001049  0000              add [bx+si],al
0000104B  0001              add [bx+di],al
0000104D  0017              add [bx],dl
0000104F  004900            add [bx+di+0x0],cl
00001052  0000              add [bx+si],al
00001054  A4                movsb
00001055  97                xchg ax,di
00001056  0408              add al,0x8
00001058  0100              add [bx+si],ax
0000105A  0000              add [bx+si],al
0000105C  0100              add [bx+si],ax
0000105E  1800              sbb [bx+si],al
00001060  55                push bp
00001061  0000              add [bx+si],al
00001063  00888404          add [bx+si+0x484],cl
00001067  0800              or [bx+si],al
00001069  0000              add [bx+si],al
0000106B  0002              add [bp+si],al
0000106D  000C              add [si],cl
0000106F  006B00            add [bp+di+0x0],ch
00001072  0000              add [bx+si],al
00001074  BC8404            mov sp,0x484
00001077  0800              or [bx+si],al
00001079  0000              add [bx+si],al
0000107B  0002              add [bp+si],al
0000107D  000C              add [si],cl
0000107F  0011              add [bx+di],dl
00001081  0000              add [bx+si],al
00001083  0000              add [bx+si],al
00001085  0000              add [bx+si],al
00001087  0000              add [bx+si],al
00001089  0000              add [bx+si],al
0000108B  0004              add [si],al
0000108D  00F1              add cl,dh
0000108F  FF7700            push word [bx+0x0]
00001092  0000              add [bx+si],al
00001094  84960408          test [bp+0x804],dl
00001098  0000              add [bx+si],al
0000109A  0000              add [bx+si],al
0000109C  0100              add [bx+si],ax
0000109E  1100              adc [bx+si],ax
000010A0  8400              test [bx+si],al
000010A2  0000              add [bx+si],al
000010A4  8C960408          mov [bp+0x804],ss
000010A8  0000              add [bx+si],al
000010AA  0000              add [bx+si],al
000010AC  0100              add [bx+si],ax
000010AE  1200              adc al,[bx+si]
000010B0  91                xchg ax,cx
000010B1  0000              add [bx+si],al
000010B3  007886            add [bx+si-0x7a],bh
000010B6  0408              add al,0x8
000010B8  0000              add [bx+si],al
000010BA  0000              add [bx+si],al
000010BC  0100              add [bx+si],ax
000010BE  1000              adc [bx+si],al
000010C0  9F                lahf
000010C1  0000              add [bx+si],al
000010C3  00909604          add [bx+si+0x496],dl
000010C7  0800              or [bx+si],al
000010C9  0000              add [bx+si],al
000010CB  0001              add [bx+di],al
000010CD  0013              add [bp+di],dl
000010CF  00AB0000          add [bp+di+0x0],ch
000010D3  00E0              add al,ah
000010D5  8504              test [si],ax
000010D7  0800              or [bx+si],al
000010D9  0000              add [bx+si],al
000010DB  0002              add [bp+si],al
000010DD  000C              add [si],cl
000010DF  00C1              add cl,al
000010E1  0000              add [bx+si],al
000010E3  0000              add [bx+si],al
000010E5  0000              add [bx+si],al
000010E7  0000              add [bx+si],al
000010E9  0000              add [bx+si],al
000010EB  0004              add [si],al
000010ED  00F1              add cl,dh
000010EF  FFC9              dec cx
000010F1  0000              add [bx+si],al
000010F3  001C              add [si],bl
000010F5  8504              test [si],ax
000010F7  0829              or [bx+di],ch
000010F9  0000              add [bx+si],al
000010FB  0002              add [bp+si],al
000010FD  000C              add [si],cl
000010FF  00D9              add cl,bl
00001101  0000              add [bx+si],al
00001103  00A89704          add [bx+si+0x497],ch
00001107  0801              or [bx+di],al
00001109  0000              add [bx+si],al
0000110B  0001              add [bx+di],al
0000110D  0018              add [bx+si],bl
0000110F  00E7              add bh,ah
00001111  0000              add [bx+si],al
00001113  000C              add [si],cl
00001115  8504              test [si],ax
00001117  0810              or [bx+si],dl
00001119  0000              add [bx+si],al
0000111B  0002              add [bp+si],al
0000111D  000C              add [si],cl
0000111F  00EF              add bh,ch
00001121  0000              add [bx+si],al
00001123  0000              add [bx+si],al
00001125  0000              add [bx+si],al
00001127  00BC0500          add [si+0x5],bh
0000112B  0012              add [bp+si],dl
0000112D  0000              add [bx+si],al
0000112F  0014              add [si],dl
00001131  0100              add [bx+si],ax
00001133  00949604          add [si+0x496],dl
00001137  0800              or [bx+si],al
00001139  0000              add [bx+si],al
0000113B  0011              add [bx+di],dl
0000113D  0014              add [si],dl
0000113F  001D              add [di],bl
00001141  0100              add [bx+si],ax
00001143  0020              add [bx+si],ah
00001145  8604              xchg al,[si]
00001147  0804              or [si],al
00001149  0000              add [bx+si],al
0000114B  0011              add [bx+di],dl
0000114D  000E0024          add [0x2400],cl
00001151  0100              add [bx+si],ax
00001153  007C96            add [si-0x6a],bh
00001156  0408              add al,0x8
00001158  0000              add [bx+si],al
0000115A  0000              add [bx+si],al
0000115C  1002              adc [bp+si],al
0000115E  F1                int1
0000115F  FF35              push word [di]
00001161  0100              add [bx+si],ax
00001163  009C9704          add [si+0x497],bl
00001167  0800              or [bx+si],al
00001169  0000              add [bx+si],al
0000116B  0011              add [bx+di],dl
0000116D  0217              add dl,[bx]
0000116F  004201            add [bp+si+0x1],al
00001172  0000              add [bx+si],al
00001174  9C                pushf
00001175  8504              test [si],ax
00001177  084200            or [bp+si+0x0],al
0000117A  0000              add [bx+si],al
0000117C  1200              adc al,[bx+si]
0000117E  0C00              or al,0x0
00001180  52                push dx
00001181  0100              add [bx+si],ax
00001183  0000              add [bx+si],al
00001185  0000              add [bx+si],al
00001187  003C              add [si],bh
00001189  0000              add [bx+si],al
0000118B  0012              add [bp+si],dl
0000118D  0000              add [bx+si],al
0000118F  006C01            add [si+0x1],ch
00001192  0000              add [bx+si],al
00001194  C8830408          enter 0x483,0x8
00001198  0000              add [bx+si],al
0000119A  0000              add [bx+si],al
0000119C  1200              adc al,[bx+si]
0000119E  0A00              or al,[bx+si]
000011A0  7201              jc 0x11a3
000011A2  0000              add [bx+si],al
000011A4  40                inc ax
000011A5  8404              test [si],al
000011A7  0800              or [bx+si],al
000011A9  0000              add [bx+si],al
000011AB  0012              add [bp+si],dl
000011AD  000C              add [si],cl
000011AF  007901            add [bx+di+0x1],bh
000011B2  0000              add [bx+si],al
000011B4  7C96              jl 0x114c
000011B6  0408              add al,0x8
000011B8  0000              add [bx+si],al
000011BA  0000              add [bx+si],al
000011BC  1002              adc [bp+si],al
000011BE  F1                int1
000011BF  FF8C0100          dec word [si+0x1]
000011C3  004885            add [bx+si-0x7b],cl
000011C6  0408              add al,0x8
000011C8  52                push dx
000011C9  0000              add [bx+si],al
000011CB  0012              add [bp+si],dl
000011CD  000C              add [si],cl
000011CF  009C0100          add [si+0x1],bl
000011D3  00A49704          add [si+0x497],ah
000011D7  0800              or [bx+si],al
000011D9  0000              add [bx+si],al
000011DB  0010              add [bx+si],dl
000011DD  00F1              add cl,dh
000011DF  FFA80100          jmp far [bx+si+0x1]
000011E3  00E8              add al,ch
000011E5  8404              test [si],al
000011E7  0824              or [si],ah
000011E9  0000              add [bx+si],al
000011EB  0012              add [bp+si],dl
000011ED  000C              add [si],cl
000011EF  00AD0100          add [di+0x1],ch
000011F3  0000              add [bx+si],al
000011F5  0000              add [bx+si],al
000011F7  00DD              add ch,bl
000011F9  0000              add [bx+si],al
000011FB  0012              add [bp+si],dl
000011FD  0000              add [bx+si],al
000011FF  00CA              add dl,cl
00001201  0100              add [bx+si],ax
00001203  007C96            add [si-0x6a],bh
00001206  0408              add al,0x8
00001208  0000              add [bx+si],al
0000120A  0000              add [bx+si],al
0000120C  1002              adc [bp+si],al
0000120E  F1                int1
0000120F  FF                db 0xFF
00001210  DB01              fild dword [bx+di]
00001212  0000              add [bx+si],al
00001214  98                cbw
00001215  97                xchg ax,di
00001216  0408              add al,0x8
00001218  0000              add [bx+si],al
0000121A  0000              add [bx+si],al
0000121C  2000              and [bx+si],al
0000121E  17                pop ss
0000121F  00E6              add dh,ah
00001221  0100              add [bx+si],ax
00001223  0004              add [si],al
00001225  8604              xchg al,[si]
00001227  0800              or [bx+si],al
00001229  0000              add [bx+si],al
0000122B  0012              add [bp+si],dl
0000122D  000D              add [di],cl
0000122F  00EC              add ah,ch
00001231  0100              add [bx+si],ax
00001233  007C96            add [si-0x6a],bh
00001236  0408              add al,0x8
00001238  0000              add [bx+si],al
0000123A  0000              add [bx+si],al
0000123C  1002              adc [bp+si],al
0000123E  F1                int1
0000123F  FF00              inc word [bx+si]
00001241  0200              add al,[bx+si]
00001243  00A49704          add [si+0x497],ah
00001247  0800              or [bx+si],al
00001249  0000              add [bx+si],al
0000124B  0010              add [bx+si],dl
0000124D  00F1              add cl,dh
0000124F  FF07              inc word [bx]
00001251  0200              add al,[bx+si]
00001253  007897            add [bx+si-0x69],bh
00001256  0408              add al,0x8
00001258  0000              add [bx+si],al
0000125A  0000              add [bx+si],al
0000125C  1100              adc [bx+si],ax
0000125E  16                push ss
0000125F  001D              add [di],bl
00001261  0200              add al,[bx+si]
00001263  00AC9704          add [si+0x497],ch
00001267  0800              or [bx+si],al
00001269  0000              add [bx+si],al
0000126B  0010              add [bx+si],dl
0000126D  00F1              add cl,dh
0000126F  FF22              jmp near [bp+si]
00001271  0200              add al,[bx+si]
00001273  007C96            add [si-0x6a],bh
00001276  0408              add al,0x8
00001278  0000              add [bx+si],al
0000127A  0000              add [bx+si],al
0000127C  1002              adc [bp+si],al
0000127E  F1                int1
0000127F  FF35              push word [di]
00001281  0200              add al,[bx+si]
00001283  0024              add [si],ah
00001285  8604              xchg al,[si]
00001287  0804              or [si],al
00001289  0000              add [bx+si],al
0000128B  0011              add [bx+di],dl
0000128D  000E0044          add [0x4400],cl
00001291  0200              add al,[bx+si]
00001293  00989704          add [bx+si+0x497],bl
00001297  0800              or [bx+si],al
00001299  0000              add [bx+si],al
0000129B  0010              add [bx+si],dl
0000129D  0017              add [bx],dl
0000129F  005102            add [bx+di+0x2],dl
000012A2  0000              add [bx+si],al
000012A4  0000              add [bx+si],al
000012A6  0000              add [bx+si],al
000012A8  0000              add [bx+si],al
000012AA  0000              add [bx+si],al
000012AC  2000              and [bx+si],al
000012AE  0000              add [bx+si],al
000012B0  650200            add al,[gs:bx+si]
000012B3  0020              add [bx+si],ah
000012B5  8404              test [si],al
000012B7  083D              or [di],bh
000012B9  0400              add al,0x0
000012BB  0012              add [bp+si],dl
000012BD  0000              add [bx+si],al
000012BF  00860200          add [bp+0x2],al
000012C3  007C96            add [si-0x6a],bh
000012C6  0408              add al,0x8
000012C8  0000              add [bx+si],al
000012CA  0000              add [bx+si],al
000012CC  1002              adc [bp+si],al
000012CE  F1                int1
000012CF  FF9C0200          call far [si+0x2]
000012D3  0000              add [bx+si],al
000012D5  0000              add [bx+si],al
000012D7  009C0000          add [si+0x0],bl
000012DB  0012              add [bp+si],dl
000012DD  0000              add [bx+si],al
000012DF  00C1              add cl,al
000012E1  0200              add al,[bx+si]
000012E3  0000              add [bx+si],al
000012E5  0000              add [bx+si],al
000012E7  0000              add [bx+si],al
000012E9  0000              add [bx+si],al
000012EB  0020              add [bx+si],ah
000012ED  0000              add [bx+si],al
000012EF  0000              add [bx+si],al
000012F1  63616C            arpl [bx+di+0x6c],sp
000012F4  6C                insb
000012F5  5F                pop di
000012F6  676D              a32 insw
000012F8  6F                outsw
000012F9  6E                outsb
000012FA  5F                pop di
000012FB  7374              jnc 0x1371
000012FD  61                popa
000012FE  7274              jc 0x1374
00001300  006372            add [bp+di+0x72],ah
00001303  7473              jz 0x1378
00001305  7475              jz 0x137c
00001307  66662E6300        o32 arpl [cs:bx+si],ax
0000130C  5F                pop di
0000130D  5F                pop di
0000130E  43                inc bx
0000130F  54                push sp
00001310  4F                dec di
00001311  52                push dx
00001312  5F                pop di
00001313  4C                dec sp
00001314  49                dec cx
00001315  53                push bx
00001316  54                push sp
00001317  5F                pop di
00001318  5F                pop di
00001319  005F5F            add [bx+0x5f],bl
0000131C  44                inc sp
0000131D  54                push sp
0000131E  4F                dec di
0000131F  52                push dx
00001320  5F                pop di
00001321  4C                dec sp
00001322  49                dec cx
00001323  53                push bx
00001324  54                push sp
00001325  5F                pop di
00001326  5F                pop di
00001327  005F5F            add [bx+0x5f],bl
0000132A  4A                dec dx
0000132B  43                inc bx
0000132C  52                push dx
0000132D  5F                pop di
0000132E  4C                dec sp
0000132F  49                dec cx
00001330  53                push bx
00001331  54                push sp
00001332  5F                pop di
00001333  5F                pop di
00001334  00702E            add [bx+si+0x2e],dh
00001337  3000              xor [bx+si],al
00001339  636F6D            arpl [bx+0x6d],bp
0000133C  706C              jo 0x13aa
0000133E  657465            gs jz 0x13a6
00001341  642E3100          xor [cs:bx+si],ax
00001345  5F                pop di
00001346  5F                pop di
00001347  646F              fs outsw
00001349  5F                pop di
0000134A  676C              a32 insb
0000134C  6F                outsw
0000134D  62616C            bound sp,[bx+di+0x6c]
00001350  5F                pop di
00001351  64746F            fs jz 0x13c3
00001354  7273              jc 0x13c9
00001356  5F                pop di
00001357  61                popa
00001358  7578              jnz 0x13d2
0000135A  006672            add [bp+0x72],ah
0000135D  61                popa
0000135E  6D                insw
0000135F  655F              gs pop di
00001361  64756D            fs jnz 0x13d1
00001364  6D                insw
00001365  7900              jns 0x1367
00001367  5F                pop di
00001368  5F                pop di
00001369  43                inc bx
0000136A  54                push sp
0000136B  4F                dec di
0000136C  52                push dx
0000136D  5F                pop di
0000136E  45                inc bp
0000136F  4E                dec si
00001370  44                inc sp
00001371  5F                pop di
00001372  5F                pop di
00001373  005F5F            add [bx+0x5f],bl
00001376  44                inc sp
00001377  54                push sp
00001378  4F                dec di
00001379  52                push dx
0000137A  5F                pop di
0000137B  45                inc bp
0000137C  4E                dec si
0000137D  44                inc sp
0000137E  5F                pop di
0000137F  5F                pop di
00001380  005F5F            add [bx+0x5f],bl
00001383  46                inc si
00001384  52                push dx
00001385  41                inc cx
00001386  4D                dec bp
00001387  45                inc bp
00001388  5F                pop di
00001389  45                inc bp
0000138A  4E                dec si
0000138B  44                inc sp
0000138C  5F                pop di
0000138D  5F                pop di
0000138E  005F5F            add [bx+0x5f],bl
00001391  4A                dec dx
00001392  43                inc bx
00001393  52                push dx
00001394  5F                pop di
00001395  45                inc bp
00001396  4E                dec si
00001397  44                inc sp
00001398  5F                pop di
00001399  5F                pop di
0000139A  005F5F            add [bx+0x5f],bl
0000139D  646F              fs outsw
0000139F  5F                pop di
000013A0  676C              a32 insb
000013A2  6F                outsw
000013A3  62616C            bound sp,[bx+di+0x6c]
000013A6  5F                pop di
000013A7  63746F            arpl [si+0x6f],si
000013AA  7273              jc 0x141f
000013AC  5F                pop di
000013AD  61                popa
000013AE  7578              jnz 0x1428
000013B0  006D61            add [di+0x61],ch
000013B3  696E2E6363        imul bp,[bp+0x2e],word 0x6363
000013B8  005F47            add [bx+0x47],bl
000013BB  4C                dec sp
000013BC  4F                dec di
000013BD  42                inc dx
000013BE  41                inc cx
000013BF  4C                dec sp
000013C0  5F                pop di
000013C1  5F                pop di
000013C2  49                dec cx
000013C3  5F                pop di
000013C4  6D                insw
000013C5  61                popa
000013C6  696E005F5A        imul bp,[bp+0x0],word 0x5a5f
000013CB  53                push bx
000013CC  7438              jz 0x1406
000013CE  5F                pop di
000013CF  5F                pop di
000013D0  696F696E69        imul bp,[bx+0x69],word 0x696e
000013D5  7400              jz 0x13d7
000013D7  5F                pop di
000013D8  5F                pop di
000013D9  7463              jz 0x143e
000013DB  665F              pop edi
000013DD  3000              xor [bx+si],al
000013DF  5F                pop di
000013E0  5A                pop dx
000013E1  4E                dec si
000013E2  53                push bx
000013E3  7438              jz 0x141d
000013E5  696F735F62        imul bp,[bx+0x73],word 0x625f
000013EA  61                popa
000013EB  7365              jnc 0x1452
000013ED  3449              xor al,0x49
000013EF  6E                outsb
000013F0  6974433145        imul si,[si+0x43],word 0x4531
000013F5  7640              jna 0x1437
000013F7  40                inc ax
000013F8  47                inc di
000013F9  4C                dec sp
000013FA  49                dec cx
000013FB  42                inc dx
000013FC  43                inc bx
000013FD  58                pop ax
000013FE  58                pop ax
000013FF  5F                pop di
00001400  332E3400          xor bp,[0x34]
00001404  5F                pop di
00001405  44                inc sp
00001406  59                pop cx
00001407  4E                dec si
00001408  41                inc cx
00001409  4D                dec bp
0000140A  49                dec cx
0000140B  43                inc bx
0000140C  005F66            add [bx+0x66],bl
0000140F  705F              jo 0x1470
00001411  687700            push word 0x77
00001414  5F                pop di
00001415  5F                pop di
00001416  66696E695F617272  imul ebp,[bp+0x69],dword 0x7272615f
0000141E  61                popa
0000141F  795F              jns 0x1480
00001421  656E              gs outsb
00001423  64005F5F          add [fs:bx+0x5f],bl
00001427  64736F            fs jnc 0x1499
0000142A  5F                pop di
0000142B  68616E            push word 0x6e61
0000142E  646C              fs insb
00001430  65005F5F          add [gs:bx+0x5f],bl
00001434  6C                insb
00001435  6962635F63        imul sp,[bp+si+0x63],word 0x635f
0000143A  7375              jnc 0x14b1
0000143C  5F                pop di
0000143D  66696E69005F5F63  imul ebp,[bp+0x69],dword 0x635f5f00
00001445  7861              js 0x14a8
00001447  5F                pop di
00001448  61                popa
00001449  7465              jz 0x14b0
0000144B  7869              js 0x14b6
0000144D  7440              jz 0x148f
0000144F  40                inc ax
00001450  47                inc di
00001451  4C                dec sp
00001452  49                dec cx
00001453  42                inc dx
00001454  43                inc bx
00001455  5F                pop di
00001456  322E312E          xor ch,[0x2e31]
0000145A  3300              xor ax,[bx+si]
0000145C  5F                pop di
0000145D  696E697400        imul bp,[bp+0x69],word 0x74
00001462  5F                pop di
00001463  7374              jnc 0x14d9
00001465  61                popa
00001466  7274              jc 0x14dc
00001468  005F5F            add [bx+0x5f],bl
0000146B  66696E695F617272  imul ebp,[bp+0x69],dword 0x7272615f
00001473  61                popa
00001474  795F              jns 0x14d5
00001476  7374              jnc 0x14ec
00001478  61                popa
00001479  7274              jc 0x14ef
0000147B  005F5F            add [bx+0x5f],bl
0000147E  6C                insb
0000147F  6962635F63        imul sp,[bp+si+0x63],word 0x635f
00001484  7375              jnc 0x14fb
00001486  5F                pop di
00001487  696E697400        imul bp,[bp+0x69],word 0x74
0000148C  5F                pop di
0000148D  5F                pop di
0000148E  627373            bound si,[bp+di+0x73]
00001491  5F                pop di
00001492  7374              jnc 0x1508
00001494  61                popa
00001495  7274              jc 0x150b
00001497  006D61            add [di+0x61],ch
0000149A  696E005F5F        imul bp,[bp+0x0],word 0x5f5f
0000149F  6C                insb
000014A0  6962635F73        imul sp,[bp+si+0x63],word 0x735f
000014A5  7461              jz 0x1508
000014A7  7274              jc 0x151d
000014A9  5F                pop di
000014AA  6D                insw
000014AB  61                popa
000014AC  696E404047        imul bp,[bp+0x40],word 0x4740
000014B1  4C                dec sp
000014B2  49                dec cx
000014B3  42                inc dx
000014B4  43                inc bx
000014B5  5F                pop di
000014B6  322E3000          xor ch,[0x30]
000014BA  5F                pop di
000014BB  5F                pop di
000014BC  696E69745F        imul bp,[bp+0x69],word 0x5f74
000014C1  61                popa
000014C2  7272              jc 0x1536
000014C4  61                popa
000014C5  795F              jns 0x1526
000014C7  656E              gs outsb
000014C9  64006461          add [fs:si+0x61],ah
000014CD  7461              jz 0x1530
000014CF  5F                pop di
000014D0  7374              jnc 0x1546
000014D2  61                popa
000014D3  7274              jc 0x1549
000014D5  005F66            add [bx+0x66],bl
000014D8  696E69005F        imul bp,[bp+0x69],word 0x5f00
000014DD  5F                pop di
000014DE  7072              jo 0x1552
000014E0  65696E69745F      imul bp,[gs:bp+0x69],word 0x5f74
000014E6  61                popa
000014E7  7272              jc 0x155b
000014E9  61                popa
000014EA  795F              jns 0x154b
000014EC  656E              gs outsb
000014EE  64005F65          add [fs:bx+0x65],bl
000014F2  6461              fs popa
000014F4  7461              jz 0x1557
000014F6  005F47            add [bx+0x47],bl
000014F9  4C                dec sp
000014FA  4F                dec di
000014FB  42                inc dx
000014FC  41                inc cx
000014FD  4C                dec sp
000014FE  5F                pop di
000014FF  4F                dec di
00001500  46                inc si
00001501  46                inc si
00001502  53                push bx
00001503  45                inc bp
00001504  54                push sp
00001505  5F                pop di
00001506  54                push sp
00001507  41                inc cx
00001508  42                inc dx
00001509  4C                dec sp
0000150A  45                inc bp
0000150B  5F                pop di
0000150C  005F65            add [bx+0x65],bl
0000150F  6E                outsb
00001510  64005F5F          add [fs:bx+0x5f],bl
00001514  696E69745F        imul bp,[bp+0x69],word 0x5f74
00001519  61                popa
0000151A  7272              jc 0x158e
0000151C  61                popa
0000151D  795F              jns 0x157e
0000151F  7374              jnc 0x1595
00001521  61                popa
00001522  7274              jc 0x1598
00001524  005F49            add [bx+0x49],bl
00001527  4F                dec di
00001528  5F                pop di
00001529  7374              jnc 0x159f
0000152B  64696E5F7573      imul bp,[fs:bp+0x5f],word 0x7375
00001531  6564005F5F        add [fs:bx+0x5f],bl
00001536  6461              fs popa
00001538  7461              jz 0x159b
0000153A  5F                pop di
0000153B  7374              jnc 0x15b1
0000153D  61                popa
0000153E  7274              jc 0x15b4
00001540  005F4A            add [bx+0x4a],bl
00001543  765F              jna 0x15a4
00001545  52                push dx
00001546  65676973746572    imul si,[gs:ebx+0x74],word 0x7265
0000154D  43                inc bx
0000154E  6C                insb
0000154F  61                popa
00001550  7373              jnc 0x15c5
00001552  657300            gs jnc 0x1555
00001555  5F                pop di
00001556  5F                pop di
00001557  677878            a32 js 0x15d2
0000155A  5F                pop di
0000155B  7065              jo 0x15c2
0000155D  7273              jc 0x15d2
0000155F  6F                outsw
00001560  6E                outsb
00001561  61                popa
00001562  6C                insb
00001563  6974795F76        imul si,[si+0x79],word 0x765f
00001568  304040            xor [bx+si+0x40],al
0000156B  43                inc bx
0000156C  58                pop ax
0000156D  58                pop ax
0000156E  41                inc cx
0000156F  42                inc dx
00001570  49                dec cx
00001571  5F                pop di
00001572  312E3300          xor [0x33],bp
00001576  5F                pop di
00001577  5F                pop di
00001578  7072              jo 0x15ec
0000157A  65696E69745F      imul bp,[gs:bp+0x69],word 0x5f74
00001580  61                popa
00001581  7272              jc 0x15f5
00001583  61                popa
00001584  795F              jns 0x15e5
00001586  7374              jnc 0x15fc
00001588  61                popa
00001589  7274              jc 0x15ff
0000158B  005F5A            add [bx+0x5a],bl
0000158E  4E                dec si
0000158F  53                push bx
00001590  7438              jz 0x15ca
00001592  696F735F62        imul bp,[bx+0x73],word 0x625f
00001597  61                popa
00001598  7365              jnc 0x15ff
0000159A  3449              xor al,0x49
0000159C  6E                outsb
0000159D  6974443145        imul si,[si+0x44],word 0x4531
000015A2  7640              jna 0x15e4
000015A4  40                inc ax
000015A5  47                inc di
000015A6  4C                dec sp
000015A7  49                dec cx
000015A8  42                inc dx
000015A9  43                inc bx
000015AA  58                pop ax
000015AB  58                pop ax
000015AC  5F                pop di
000015AD  332E3400          xor bp,[0x34]
000015B1  5F                pop di
000015B2  5F                pop di
000015B3  676D              a32 insw
000015B5  6F                outsw
000015B6  6E                outsb
000015B7  5F                pop di
000015B8  7374              jnc 0x162e
000015BA  61                popa
000015BB  7274              jc 0x1631
000015BD  5F                pop di
000015BE  5F                pop di
000015BF  00                db 0x00
