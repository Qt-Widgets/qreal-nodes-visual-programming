@@SUBPROGRAMS_FORWARDING@@

@@THREADS_FORWARDING@@

@@SUBPROGRAMS@@

@@THREADS@@

@@MAIN_CODE@@

function callback(event)
	print(event)
	if (event == Ev.ALTITUDE_REACHED) then
		action[curr_state]()
	end

	if (event == Ev.POINT_REACHED) then
		action[curr_state]()
	end

	if (event == Ev.COPTER_LANDED) then
		action[curr_state]()
	end

end

function loop()
end

ap.push(Ev.ENGINES_ARM)
action[curr_state]()