USE medicalSystem
GO

DROP TABLE Hospital
go

if exists (select * from sysobjects where name = 'fk_Hospital')

ALTER TABLE Hospital
DROP CONSTRAINT fk_Hospital


if exists (select * from sysobjects where name = 'Hospital')
BEGIN
	PRINT 'ALREADY EXISTS Hospital'
	DROP TABLE Hospital
END
else
BEGIN
CREATE TABLE [dbo].[Hospital](
 医院名称 nvarchar(40) NOT NULL UNIQUE,
 医院等级 nvarchar(4) NULL,
医院类型 nvarchar(4) NULL,
省 nvarchar(10) NULL,
市 nvarchar(10) NULL,
县 nvarchar(20) NULL,
床位数 int NULL,
医院地址 nvarchar(60) NULL,
邮编 varchar(100) NULL,
constraint pk_Hospital PRIMARY KEY
			NONCLUSTERED(医院名称),
--CONSTRAINT fk_Hospital FOREIGN KEY(邮编)
		--REFERENCES hy_area(zip_code)
)
END



--CREATE TRIGGER tr_addCode ON Hospital
--before


DELETE FROM Hospital
GO

INSERT INTO Hospital( 医院名称,医院等级,医院类型,省,市,县,床位数, 医院地址) VALUES
('河北大学附属医院','三级甲等','综合医院','河北省','保定市','莲池区',2300,'保定市莲池区裕华东路212号'),
('保定市第一中心医院','三级甲等','综合医院','河北省','保定市','莲池区',2100,'保定市莲池区长城北大街320号'),
('沧州市人民医院','三级甲等','综合医院','河北省','沧州市','新华区',3000,'沧州市清池大道7号'),
('沧州市中心医院','三级甲等','综合医院','河北省','沧州市','新华区',	4700,'沧州市新华中路201号'),
('承德医学院附属医院','三级甲等','综合医院','河北省','承德市','双桥区',2400,'承德市南营子大街36号')
GO


SELECT * FROM Hospital
SELECT * FROM department









INSERT INTO Hospital VALUES
	('河北大学附属医院','三级甲等','综合医院','河北省','保定市','莲池区',2300,'保定市莲池区裕华东路212号'),
('保定市第一中心医院','三级甲等','综合医院','河北省','保定市','莲池区',2100,'保定市莲池区长城北大街320号'),
('沧州市人民医院','三级甲等','综合医院','河北省','沧州市','新华区',3000,'沧州市清池大道7号'),
('沧州市中心医院','三级甲等','综合医院','河北省','沧州市','新华区',	4700,'沧州市新华中路201号'),
('承德医学院附属医院','三级甲等','综合医院','河北省','承德市','双桥区',2400,'承德市南营子大街36号'),
('兰州大学第二附属医院','三级甲等','综合医院','甘肃省','兰州市',	'城关区',	3500	,'城关区萃英门80号'),
('大连医科大学附属第一医院','三级甲等','综合医院','辽宁省','大连市',	'沙河口区',	3700	,'大连市中山路222号'),
('恩施州中心医院','三级甲等','综合医院','湖北省','恩施土家族苗族自治州'	,'恩施市',	2300,	'恩施市舞阳大街158号(西医部);恩施市航空大道178号(中医部)'),
('佛山市第一人民医院','三级甲等','综合医院','广东省','佛山市','南海区',2500	,'佛山市大佛南路3号'),
('南方医科大学顺德医院','三级甲等','综合医院','广东省','佛山市','顺德区',	2100	,'佛山市顺德区大良蓬莱路1号'),
('福建医科大学附属协和医院','三级甲等','综合医院','福建省','福州市','鼓楼区',	2500	,'福州市鼓楼区新权路29号'),
('阜阳市人民医院','三级甲等','综合医院','安徽省','阜阳市','颍州区',	2447	,'阜阳市鹿祠街63号'),
('广州中医药大学第一附属医院','三级甲等','综合医院','广东省','广州市','白云区',	2200	,'广州市白云区机场路16号'),
('哈尔滨医科大学附属肿瘤医院','三级甲等','专科医院','黑龙江省','哈尔滨市','南岗区',	2200	,'哈尔滨市南岗区哈平路150号'),
('哈尔滨医科大学附属第二医院','三级甲等','综合医院','黑龙江省','哈尔滨市','南岗区',	6012	,'哈尔滨市南岗区学府路246号'),
('黑龙江省医院','三级甲等','综合医院','黑龙江省','哈尔滨市','香坊区',	2442	,'哈尔滨市中山路82号'),
('海南省人民医院','三级甲等','综合医院','海南省','海口市','秀英区',	3000	,'海口市秀英区秀华路19号'),
('邯郸市第一医院','三级甲等','综合医院','河北省','邯郸市','丛台区',	3103	,'邯郸市丛台路24号'),
('邯郸市中心医院','三级甲等','综合医院','河北省','邯郸市','邯山区',2745	,'邯郸市维明路20号'),
('浙江省立同德医院','三级甲等','综合医院','浙江省','杭州市','西湖区',2100	,'杭州市古翠')

GO
SELECT*FROM Hospital
GO


