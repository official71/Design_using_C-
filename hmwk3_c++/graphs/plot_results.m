m = csvread('results.csv', 1, 0);

[R,C] = size(m);
T = R/3;
% size, prep time avg & stddev, 
% (insert time avg & stddev, remove time avg & stddev) * (vector, list, set)
P = zeros(T, 15);
for t = 1:T
    subm = m(3*t-2:3*t, :);
    P(t, 1) = log10(subm(1, 1));
    P(t, 2) = mean(subm(:, 2));
    P(t, 3) = std(subm(:, 2));
    P(t, 4) = mean(subm(:, 3));
    P(t, 5) = std(subm(:, 3));
    P(t, 6) = mean(subm(:, 4));
    P(t, 7) = std(subm(:, 4));
    P(t, 8) = mean(subm(:, 5));
    P(t, 9) = std(subm(:, 5));
    P(t, 10) = mean(subm(:, 6));
    P(t, 11) = std(subm(:, 6));
    P(t, 12) = mean(subm(:, 7));
    P(t, 13) = std(subm(:, 7));
    P(t, 14) = mean(subm(:, 8));
    P(t, 15) = std(subm(:, 8));
end

% plot insertion
figure;
hold on;
lData = errorbar(P(:,1), P(:,8), P(:,9));
set(lData, 'LineStyle','-','LineWidth',1.2,'Color',[0 0 .2], ...
    'Marker','d','MarkerSize',10,'MarkerFaceColor',[0 .3 .5]);
sData = errorbar(P(:,1), P(:,12), P(:,13));
set(sData, 'LineStyle','--','LineWidth',1.2,'Color',[.2 0 .1], ...
    'Marker','^','MarkerSize',10,'MarkerFaceColor',[.7 0 .1]);
vData = errorbar(P(:,1), P(:,4), P(:,5));
set(vData, 'LineStyle','-.','LineWidth',1.2,'Color',[0 .3 0], ...
    'Marker','o','MarkerSize',10,'MarkerFaceColor',[0 .7 .7]);
xlim([0.95, 5.4]);
ylim([-20000, inf]);
set(gca, 'XTick', P(:,1));
set(gca, 'XTickLabelRotation', 45);
set(gca, 'XTickLabel', str2mat('10','500','2000','10000','50000','100000','200000'));
set(gca, 'YTick', [0 20000 50000 150000 300000]);
set(gca, 'YTickLabel', str2mat('0 sec','20 sec','50 sec','150 sec','300 sec'));
hold off;

% plot deletion
figure;
hold on;
lData1 = line(P(:,1), P(:,10));
set(lData1, 'LineStyle','-','LineWidth',1.2,'Color',[0 0 .2], ...
    'Marker','d','MarkerSize',10,'MarkerFaceColor',[0 .3 .5]);
sData1 = line(P(:,1), P(:,14));
set(sData1, 'LineStyle','--','LineWidth',1.2,'Color',[.2 0 .1], ...
    'Marker','^','MarkerSize',10,'MarkerFaceColor',[.7 0 .1]);
vData1 = line(P(:,1), P(:,6));
set(vData1, 'LineStyle','-.','LineWidth',1.2,'Color',[0 .3 0], ...
    'Marker','o','MarkerSize',10,'MarkerFaceColor',[0 .7 .7]);
xlim([0.95, 5.4]);
ylim([-20000, 520000]);
set(gca, 'XTick', P(:,1));
set(gca, 'XTickLabelRotation', 45);
set(gca, 'XTickLabel', str2mat('10','500','2000','10000','50000','100000','200000'));
set(gca, 'YTick', [0 20000 50000 150000 300000 500000]);
set(gca, 'YTickLabel', str2mat('0 sec','20 sec','50 sec','150 sec','300 sec','500 sec'));
hold off;