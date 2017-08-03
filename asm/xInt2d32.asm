.model flat
.code 

___x_int2d proc
%ifdef X_USE_DEBUGGER_DETECTION
    int 2dh
    nop
    ret
%endif
___x_int2d endp

end
