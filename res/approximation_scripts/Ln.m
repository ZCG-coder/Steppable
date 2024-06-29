%% Padé approximation of natural logarithms
% This file contains the code to approximate the natural logarithm ($\ln x$) 
% using Padé approximation. The |pade| function provides approximation for many 
% functions.
%% 
% *Preparation*: Clear everything and set formatting.

clc
format loose

syms x
f = log(x); % f is the natural logarithm of x
%% 
% *Approximation*: Try to find the best approximant of the natural logarithm.
% 
% _Note_:
%% 
% * Drag the slider to adjust the center of the Padé approximant.
% * 1 seems to produce a clear and simple output.

a =1;

% 1 is the best for now...
% error: 0.0105

g = pade(f, x, a, 'Order', [5 5])
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