#SO_LONG

define pm
	set $map = $arg0
	set $y = 0
	while $map[$y]
		set $x = 0
		while $map[$y][$x]
            printf "[%c]", $map[$y][$x]
			set $x = $x + 1
		end
		printf "\n"
		set $y = $y + 1
	end
end



define printm
    set $map = $arg0
    set $max_y = $arg1
    set $max_x = $arg2
    set $y = 0
    while $y < $max_y
        set $x = 0
        while $x < $max_x
            printf "[%c]", $map[$y][$x]
            set $x = $x + 1
        end
        printf "\n" 
        set $y = $y + 1
    end
end
document printm
SO_LONG
arg0 = map
arg1 = max_y
arg2 = max_x
print codes of entire map
end

define pms
	set $map = $arg0
	set $iter = 0
	while $iter < 8
		set $jter = 0
		while $jter < 15
			if $map[$iter][$jter].oob == 0
				printf "[%c]", $map[$iter][$jter].map_src->tile->code
			else
				printf "[9]"
			end
			set $jter = $jter + 1
		end
		printf "\n"
		set $iter = $iter + 1
	end
end
document pms
SO_LONG
print codes of entire map_segment
end
