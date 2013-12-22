function out = Convert(filePath, fileIn, fileOut)
cd(filePath);
load(fileIn);
dlmwrite(fileOut, [numel(x) numel(t)], '\n');
dlmwrite(fileOut,[x t] ,'-append', 'delimiter', ' ');
out = 1;