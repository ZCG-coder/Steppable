%% Padé approximation of cosine
% This file contains the code to approximate cosine using Padé approximation. 
% The |pade| function provides approximation for many functions.
%% 
% *Preparation*: Clear everything and set formatting.

clc
format loose
format short

syms x
f = cos(x); % f is the cosine value of x
%% 
% *Approximation*: Try to find the best approximant of cosine.
% 
% _Note_:
%% 
% * Drag the slider to adjust the center of the Padé approximant.
% * 0 seems to produce a clear and simple output.

a =0;

% 1 is the best for now...
% error: 0.0105

g = pade(f, x, a, 'Order', [6 5])
e = abs(f - g);
%% 
% *Evaluation*: Find the errors of the approximation.

x_values = linspace(0, 1, 1e2);
err = double(subs(e, x, x_values));
mean(err, 'omitnan')
%% 
% *Visualization*: Graph the errors and see the covergence.

figure
hold off
hold on
fplot(g, [-1 1])
fplot(f, [-1 1])
plot(err)

title('Error of Padé approximants of ln(x)')
legend('g (approximated)', 'f', 'error')
xlabel('x')
ylabel('error')