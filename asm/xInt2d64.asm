.code 

__x_int2d proc
%ifdef X_USE_DEBUGGER_DETECTION
    int 2dh
    nop
	ret
%endif
__x_int2d endp

end
