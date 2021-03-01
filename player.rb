v0 = play 60, amp: 0, attack: 0.5, sustain: 7200, release: 0.5, note_slide: 0.3, amp_slide: 0.3
v1 = play 60, amp: 0, attack: 0.5, sustain: 7200, release: 0.5, note_slide: 0.3, amp_slide: 0.3
v2 = play 60, amp: 0, attack: 0.5, sustain: 7200, release: 0.5, note_slide: 0.3, amp_slide: 0.3
v3 = play 60, amp: 0, attack: 0.5, sustain: 7200, release: 0.5, note_slide: 0.3, amp_slide: 0.3

voices = [v0, v1, v2, v3]


live_loop :vol_change do
  use_real_time
  v, a = sync "/osc*/vol"
  control voices[v], amp: a
end

live_loop :pitch_change do
  use_real_time
  v, n = sync "/osc*/pitch"
  control voices[v], note: n
end

